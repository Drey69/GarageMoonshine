/*
 * mainCpp.cpp
 *
 *  Created on: Jun 7, 2022
 *      Author: Drey
 */
#define testing

#include "TempSpirtTable.h"
#include "stm32f1xx_hal.h"
#include "Screen.h"
#include "mainCpp.h"
#include "main.h"
#include "classEncoder.h"
#include "Ten.h"
#include "classOnewire.h"
#include "classButton.h"
#include "classPeepok.h"
#include "ssd1306.h"
#include "menuItems.h"
#include "classMenu.h"
#include "usart_ring.h"
#include "SenderUart.h"
#include "math.h"

using namespace Menuu;

extern TIM_HandleTypeDef htim4;
extern TIM_HandleTypeDef htim2;
extern RTC_HandleTypeDef hrtc;

int encCounter;
const uint8_t PERCENT_HEADS = 10; //  отбор 10 % от Абсолютного спирта
SenderUart sender;
Encoder encoder;
Screen screen;
Ten ten;
classOnewire tempCube;
classOnewire tempColumn;
Button encoderButton;
Button buttonGo;
State status;
Pipka beeper;
RTC_TimeTypeDef zeroTime = {0,0,0};

#ifndef testing
uint8_t romCube[] = {40, 193, 214, 118, 224, 1, 60, 203};
uint8_t romColumn[] = {40, 29, 157, 118, 224, 1, 60, 235 };
#else
 uint8_t romColumn[] = {40, 38, 147, 118, 224, 1, 60, 92 };
 uint8_t romCube[] = {40, 214, 35, 118, 224, 1, 60, 97};
#endif
uint8_t secondFlag;

// прерывание по енкодеру
void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim){
	if(htim->Instance == TIM4)	{
		if (__HAL_TIM_IS_TIM_COUNTING_DOWN(&htim4)) encCounter--;
		else encCounter++;
	}
}
///////////////////////////////////////////////////////////////////////////////////////////
void init()
{

	secondFlag = 0;
	status.mode = wm_off;
	status.power = 0;
	HAL_RTC_GetTime(&hrtc, &status.time, RTC_FORMAT_BIN);
	beeper.init(beeper_GPIO_Port, beeper_Pin);
	buttonGo = Button(Button1_GPIO_Port, Button1_Pin);
	encoderButton = Button(EncoderButton_GPIO_Port, EncoderButton_Pin);
	encCounter = 0;
	encoder.clearSteps();
	delay(300);
	screen.init();
	screen.clearScreen();
	ten.init();
	tempCube = classOnewire(&htim2, Ds18b20_GPIO_Port, Ds18b20_Pin, romCube);
//	tempCube.readRom();
	tempColumn = classOnewire(&htim2, Ds18b20_GPIO_Port, Ds18b20_Pin, romColumn);
//	tempColumn.readRom();
	tempCube.convertALL();
	beeper.playBlocking(m_deviceStart);
	screen.setStatus(&status);
	sender.sendStatus(status);

}
void delay(int ms){HAL_Delay(ms);}
//--------------------------------------------------------
void loop()
{
	int lastMessegaTime = HAL_GetTick();;
	RTC_TimeTypeDef timeNow;
	HAL_RTC_GetTime(&hrtc, &timeNow, RTC_FORMAT_BIN);
	int encoderButtonState, buttonGoState;
	uint8_t selectedItem = sel_power;
	Menuu::Menu mainMenu;
	mainMenu.init(mainMenuItems, mainMenuItemCount);
	uint32_t encoderCounter = 0;
 	ten.start(0);
//	tempCube.readRom();
	tempCube.convertALL();
	mainMenu.run();
	HAL_RTC_GetTime(&hrtc, &status.timeCurrentMode, RTC_FORMAT_BIN);
	//while(!tempCube.isConversionComplete());
	while(true)
	{

		encoderButtonState = encoderButton.tick();
		buttonGoState = buttonGo.tick();
		HAL_RTC_GetTime(&hrtc, &timeNow, RTC_FORMAT_BIN);
		if (status.time.Seconds != timeNow.Seconds)   status.time = timeNow;

		if ( tempCube.isConversionComplete())
		{
			status.cubeTemp = tempCube.getTemperature();
			status.columnTemp = tempColumn.getTemperature();
			screen.setCubeTemp(status.cubeTemp);
			screen.setColumnTemp(status.columnTemp);
			tempCube.convertALL();
		}
		workTick();									//главный рабочий функция --- установка мощи тена в ней
		encoder.tick(&encCounter);
		if (HAL_GetTick() > (uint32_t)(SEND_TIME_PERIOD + lastMessegaTime))
		{
			lastMessegaTime = HAL_GetTick();
			sender.sendStatus(status);
			beeper.playBlocking(m_changeMode);
		}
		if (encoder.available())
		{
			if (encoder.isRight() )
			{
				switch (selectedItem)
				{
				case sel_power:
					if ( status.mode != wm_off && status.mode != wm_over_ok)
					{
						status.power += 5;
						if ( status.power > 100) status.power = 100;
					}
					break;
				case sel_ColumnTempConf:
					status.columnTempConfigured += 0.2;
					break;
				case sel_cubeTempConf:
					status.cubeTempConfigured += 1;
					break;
				case sel_mode:
					status.mode = (mainWorkMode)( status.mode +1);
					HAL_RTC_GetTime(&hrtc, &status.timeCurrentMode, RTC_FORMAT_BIN);
					if (status.mode >= mainWorkModeCount)
						status.mode = (mainWorkMode)0;
					break;
				default :
					break;
				}
			}
			if (encoder.isLeft())
			{
				switch (selectedItem)
				{
					case sel_power:
						//if ( status.mode != wm_off && status.mode != wm_over_ok)
							if (status.power >= 5) status.power -= 5;
						break;
					case sel_ColumnTempConf:
						if (status.columnTempConfigured > 0.2)
							status.columnTempConfigured -= 0.2;
						break;
					case sel_cubeTempConf:
						if ( status.cubeTempConfigured > 1)
							status.cubeTempConfigured -= 1;
						break;
				   case sel_mode:
						if (status.mode == 0)
							status.mode = (mainWorkMode)(mainWorkModeCount-1);
						else status.mode = (mainWorkMode)(status.mode -1);
						break;
				  default :
					  break;
				}
				screen.setPower(encoderCounter);
			}
		}
		if (encoderButtonState == state_hold)
		{
			status.time = zeroTime;
			mainMenu.run();
		}
		if (buttonGoState == state_click)
		{
			++selectedItem;
			if (selectedItem >= SelectedItemCount) selectedItem = 0;
			screen.setSelItem(selectedItem);
		}
		screen.setStatus(&status);
		screen.updateScreen();
	}
}
//-------------------------------------главный рабочий тик
void workTick()
{
	static RTC_TimeTypeDef timeStruct;
	static int timeMinutes;
	HAL_RTC_GetTime(&hrtc, &timeStruct, RTC_FORMAT_BIN);
	timeMinutes = timeDefTumin(&timeStruct);
	timeMinutes = timeMinutes;
	if ( status.mode == wm_firstHeating || status.mode == wm_secondHeating ) // если включен режим предподогрева
	{
		if ( status.cubeTemp < status.cubeTempConfigured)// если еще греется
		{

		}
		else 	//если нагрелось пищим что нагрелося и утсанавливаем режим ожидания
		{
			beeper.playBlocking(m_changeMode);
			setWaitMode();
		}
		ten.start(status.power);
		return;
	}

	if ( status.mode == wm_first ) // первый перегон
	{
		if ( status.columnTemp > status.columnTempConfigured || status.cubeTemp > status.cubeTempConfigured) // перегрев
		{
			beeper.playBlocking(m_changeMode);
			setOver();
		}
		ten.start(status.power);
		return;
	}

	if ( status.mode == wm_manual) //все ручное без тревог и ограничений
	{
		ten.start(status.power);
		return;
	}

	if ( status.mode == wm_secondHeating)
	{
		if ( tempCube.isStable() )
		{												//	если куб стабилизировался
			beeper.playBlocking(m_changeMode);
			status.mode = wm_secondGetHeads; //  перходим в режим автоматического отбора голов
			status.stableCubeTemp = tempCube.temperature; //сохраняем стабильную температуру
		}
	}
	if ( status.mode == wm_second)
	{
		if ( status.columnTemp < status.columnTempConfigured ) //работа
		{
			if (status.cubeTemp > status.cubeTempConfigured) // перегрев в кубе на втором режиме уже как ошибка
			{
				beeper.playBlocking(m_error);
				setWaitMode();
			}
		}
		else //перегрев
		{
			beeper.playBlocking(m_changeMode);
			setWaitMode();
		}
		if (status.cubeTemp > status.cubeTempConfigured) // перегрев в кубе значит конец перегона
		{
			beeper.playBlocking(m_changeMode);
			setWaitMode();
		}
		ten.start(status.power);
		return;
	}

	if ( status.mode == wm_secondGetHeads) // отбор ГОЛОВ тут все сложно)))
	{		// усли только зашли в этот режим высчитываем до какой температуры отбирать
		if (status.stopGetHeadsTemp == 0 && status.stableCubeTemp != 0 && tempCube.isStable())
		{//Получаем что х =52*90/100=46.8%
			int alcoNow = findAlcoholPercentByTemp(status.stableCubeTemp);
			int alcoStop = round( (float)alcoNow * (float)(100.0- PERCENT_HEADS) / 100.0 );
			status.stopGetHeadsTemp = findTempByAlcohol(alcoStop);
		}
		if (status.stopGetHeadsTemp != 0 && status.stopGetHeadsTemp < status.cubeTemp)
		{		// 	отобрались головы
			// както надо определиттся в какой режим уходить или сделать настройку пожже
			status.mode = wm_wating;
			beeper.playBlocking(m_alarm);
		}


		ten.start(status.power);
		return;
	}

	if ( status.mode == wm_secondGetBody)
	{
		if (status.cubeTemp < status.cubeTempConfigured) //work
		{

		}
		else //перегрев
		{
			beeper.playBlocking(m_changeMode);
			setWaitMode();
		}
		ten.start(status.power);
		return;
	}

	if (status.mode == wm_secondsGetTail)
	{
		if (status.cubeTemp > status.cubeTempConfigured || status.columnTemp > status.columnTempConfigured) //перегрев
		{
			beeper.playBlocking(m_changeMode);
			setOver();
		}
		ten.start(status.power);
		return;
	}

	ten.start(status.power);
}
//------------------------------------------------------------------------
uint32_t getEncoderMoves()
{
	return __HAL_TIM_GET_COUNTER(&htim4);
}
//-------------------------------------------------------------------------
uint32_t timeDefTumin(RTC_TimeTypeDef * time) //перегон структуры времени в минуты
{
	return time->Hours * 60 + time->Minutes;
}
void mainMenuheat1(void)
{
	status.mode =wm_firstHeating;
	status.power = PREHEAT_POWER;
	status.time = zeroTime;
	status.cubeTempConfigured = CUBE_PREHEAT_MODE1_STOP;
}
void mainMenuheat2(void)
{
	status.mode =wm_secondHeating;
	status.power = PREHEAT_POWER;
	status.time = zeroTime;
	status.cubeTempConfigured = CUBE_PREHEAT_MODE2_STOP;
}
void mainMenuMode1(void)
{
	status.mode =wm_first;
	status.power = HEAT_BODY2_POWER;
	status.time = zeroTime;
	status.cubeTempConfigured = CUBE_MOD1_SELECTION_MAX;
	status.columnTempConfigured = COLUMN_MAX;
}
void mainMenuMode2(void)
{
	status.mode =wm_second;
	status.power = HEAT_BODY2_POWER;
	status.time = zeroTime;
	status.cubeTempConfigured = CUBE_BODY_SELECTION_MAX;
	status.columnTempConfigured = COLUMN_MAX;
}
void mainMenuManual(void)
{
	status.mode =wm_manual;
	status.power = 0;
	status.time = zeroTime;
	status.cubeTempConfigured = CUBE_PREHEAT_MODE2_STOP;
	status.columnTempConfigured = COLUMN_MAX;
}
void mainMenuExit(void)
{
	status.mode =wm_off;
	status.power = 0;
	status.time = zeroTime;
	status.cubeTempConfigured = CUBE_PREHEAT_MODE2_STOP;
	status.columnTempConfigured = COLUMN_MIN;
}
void mainMenuGetHead(void)
{
	status.mode = wm_secondGetHeads;
	status.power = HEAT_HEADS_POWER;
	status.cubeTempConfigured = CUBE_BODY_SELECTION_MAX;
	status.columnTempConfigured = COLUMN_MAX;
	status.time = zeroTime;
}
void mainMenuGetBody(void)
{
	status.mode = wm_secondGetBody;
	status.power = HEAT_BODY2_POWER;
	status.cubeTempConfigured = CUBE_BODY_SELECTION_MAX;
	status.columnTempConfigured = COLUMN_MAX;
	status.time = zeroTime;
}
void mainMenuGetTail(void)
{
	status.mode = wm_secondsGetTail;
	status.power = HEAT_BODY1_POWER;
	status.cubeTempConfigured = CUBE_TAIL_SELECTION_MAX;
	status.columnTempConfigured = COLUMN_MAX;
	status.time = zeroTime;
}

void setWaitMode(void)
{
	status.mode =wm_wating;
	status.power = HEAT_WAITING_POWER;
	status.time = zeroTime;
	status.cubeTempConfigured = CUBE_MOD1_SELECTION_MAX;
	status.columnTempConfigured = COLUMN_MIN;
}
void setOver(void)
{
	status.mode = wm_over_ok;
	status.power = 0;
}
void setStop(void)
{
	status.mode = wm_off;
	status.time = zeroTime;
	status.power = 0;
}

uint8_t findAlcoholPercentByTemp(float t)
{
	uint8_t i = 0;
	for(   ; i < 41; i++)
		if (SpirtBoilingDependence[i] < t)  break;
	return i + 10; //ибо от 10 до 50% таблица
}

float findTempByAlcohol(uint8_t gradusy)
{
	if (gradusy < 10 || gradusy > 50)  return 0;
	//т к массив температур от 10 % и до 50% 41 позиция в массиве
	return SpirtBoilingDependence[gradusy-10];
}
