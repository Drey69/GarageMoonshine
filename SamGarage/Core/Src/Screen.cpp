/*
 * Screen.cpp
 *
 *  Created on: Jun 8, 2022
 *      Author: Drey
 */
#include "stm32f1xx_hal.h"
#include "Screen.h"

const uint32_t timeToWait = 200; //перерыв между кадрами
extern RTC_HandleTypeDef hrtc;
Screen::Screen()
{
}

void Screen::clearScreen()
{
	ssd1306_Fill(Black);
}

void Screen::init()
{
	modeNames[0] = (char*) "OFF";
	modeNames[1] = (char*)"1 WORK";
	modeNames[2] = (char*)"1 HEAT";
	modeNames[3] = (char*)"2 WORK";
	modeNames[4] = (char*)"2 HEAT";
	modeNames[5] = (char*)"HEADS";
	modeNames[6] = (char*)"BODY";
	modeNames[7] = (char*)"TAIL";
	modeNames[8] = (char*)"MANUAL";
	modeNames[9] = (char*)"WAIT";
	modeNames[10] = (char*)"OVER";
	changedData = true;
	millis = HAL_GetTick();
	ssd1306_Init();
	char str[] = "HI !";
	ssd1306_Fill(Black);
	ssd1306_SetCursor(40, 20);
	ssd1306_WriteString(str, Font_11x18, White);
	ssd1306_UpdateScreen();
	//---------------------------------------------
	HAL_RTC_GetTime(&hrtc, &time, RTC_FORMAT_BIN);
	//HAL_Delay(300);
}

void Screen::clearTime()
{
	time.Hours = 0;
	time.Minutes = 0;
	time.Seconds = 0;
	HAL_RTC_SetTime (&hrtc, &time, RTC_FORMAT_BIN);
}

void Screen::updateScreen()
{

	uint32_t now = HAL_GetTick();
	if (timeToWait < (now - millis))	millis = now;
	else if ( !changedData) return;
	char strTime[10] = {0,};
	char strPower[5] = {0,};
	HAL_RTC_GetTime(&hrtc, &time, RTC_FORMAT_BIN);
	timeToStr(strTime);
	powerToStr(strPower);
	ssd1306_Fill(Black);
	ssd1306_SetCursor(posTime.X, posTime.Y);
	ssd1306_WriteString(strTime, posTime.Font, White);
	ssd1306_SetCursor(posPower.X, posPower.Y);
	ssd1306_WriteString(strPower, posPower.Font, White);
	ssd1306_SetCursor(posCubeTemp.X, posCubeTemp.Y);
	ssd1306_WriteString(strTempCube, posCubeTemp.Font, White);
	ssd1306_SetCursor(posColTemp.X, posColTemp.Y);
	ssd1306_WriteString(strTempCol, posColTemp.Font, White);
	ssd1306_SetCursor(posCubeTempConf.X, posCubeTempConf.Y);
	ssd1306_WriteString(strTempCubeConf, posCubeTempConf.Font, White);
	ssd1306_SetCursor(posColTempConf.X, posColTempConf.Y);
	ssd1306_WriteString(strTempColConf, posColTempConf.Font, White);
	ssd1306_SetCursor(posMode.X, posMode.Y);
	ssd1306_WriteString(modeNames[state.mode], posMode.Font, White);
	switch ( selItem)
	{
	case sel_power:
		ssd1306_DrawRectangle(rectPower.x1, rectPower.y1, rectPower.x2, rectPower.y2, White);
		break;
	case sel_ColumnTempConf:
		ssd1306_DrawRectangle(rectTempColConf.x1, rectTempColConf.y1, rectTempColConf.x2, rectTempColConf.y2, White);
		break;
	case sel_cubeTempConf:
		ssd1306_DrawRectangle(rectTempCubeConf.x1, rectTempCubeConf.y1, rectTempCubeConf.x2, rectTempCubeConf.y2, White);
		break;
	case sel_mode:
		ssd1306_DrawRectangle(rectMode.x1, rectMode.y1, rectMode.x2, rectMode.y2, White);
		break;
	default:
		break;
	}
	ssd1306_UpdateScreen();
	changedData = false;
}

void Screen::timeToStr(char *str){
	char digit[5];
	itoa(state.time.Hours, digit, 10);
	if (state.time.Hours < 10)
	{
		str[0] = '0';
		str[1] = digit[0];
	}
	else {
		str[0] = digit[0];
		str[1] = digit[1];
	}
	str[2] = ':';
	itoa(state.time.Minutes, digit, 10);
	if (state.time.Minutes < 10)
	{
		str[3] = '0';
		str[4] = digit[0];
	}
	else {
		str[3] = digit[0];
		str[4] = digit[1];
	}
	str[5] = ':';
	itoa(state.time.Seconds, digit, 10);
		if (state.time.Seconds < 10)
		{
			str[6] = '0';
			str[7] = digit[0];
		}
		else {
			str[6] = digit[0];
			str[7] = digit[1];
		}
		str[8] = 0;
}

void Screen::setPower(uint32_t pow)
{
	state.power = pow;
	changedData = true;
}

void Screen::setColumnTemp(float colTemp)
{
	state.columnTemp = colTemp;
	clearArr(strTempCol, 7);
	floatToStr(strTempCol, colTemp);
	changedData = true;
}

void Screen::setCubeTemp(float cubeTemp)
{
	state.cubeTemp = cubeTemp;
	clearArr(strTempCube, 7);
	floatToStr(strTempCube, cubeTemp);
	changedData = true;
}

void Screen::powerToStr(char *str)
{
	str[0] = '%';
	str[1] = ' ';
	itoa(state.power, str+2, 10);
}

void Screen::setStatus(State* st)
{
	if (state.columnTemp != st->columnTemp)
	{
		state.columnTemp = st->columnTemp;
	    changedData = true;
	}
	if (state.columnTempConfigured != st->columnTempConfigured)
	{
		state.columnTempConfigured = st->columnTempConfigured;
	    changedData = true;
	}
	if (state.cubeTemp != st->cubeTemp)
	{
		state.cubeTemp = st->cubeTemp;
	    changedData = true;
	}
	if (state.cubeTempConfigured != st->cubeTempConfigured)
	{
		state.cubeTempConfigured = st->cubeTempConfigured;
		changedData = true;
	}
	if (state.mode != st->mode)
	{
		state.mode = st->mode;
		changedData = true;
	}
	if (state.power != st->power)
	{
		state.power = st->power;
		changedData = true;
	}
	state.time = st->time;
//---------------------------------------------------
	setColumnTemp(state.columnTemp);
	setColumnTempConf(state.columnTempConfigured);
	setCubeTemp(state.cubeTemp);
	setCubeTempConf(state.cubeTempConfigured);
	setPower(state.power);

}

void Screen::floatToStr(char *str, const float t)
{
	int tempT = t * 10;
	itoa ( tempT/10, str, 10);
	if (t >= 100) str += 3;
	else str += 2;
	*str = '.';
	str++;
	itoa ( tempT % 10, str, 10);
}

void Screen::setSelItem(uint8_t item)
{
	selItem = item;
}

void Screen::setColumnTempConf(float colTempConf)
{
	state.columnTempConfigured = colTempConf;
	clearArr(strTempColConf, 7);
	floatToStr(strTempColConf, colTempConf);
	changedData = true;
}

void Screen::setCubeTempConf(float cubeTempConf)
{
	state.cubeTempConfigured = cubeTempConf;
	clearArr(strTempCubeConf, 7);
	floatToStr(strTempCubeConf, cubeTempConf);
	changedData = true;
}

void Screen::clearArr(char *arr, int len)
{
	for ( int i = 0; i < len; i++)
	{
		*(arr+i) = 0;
	}


}
