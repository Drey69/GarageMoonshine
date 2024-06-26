/*
 * mainCpp.h
 *
 *  Created on: Jun 7, 2022
 *      Author: Drey
 */

#ifndef INC_MAINCPP_H_
#define INC_MAINCPP_H_
#include "stm32f1xx_hal.h"
const float CUBE_PREHEAT_MODE1_STOP = 85;
const float CUBE_PREHEAT_MODE2_STOP = 70;
const float CUBE_MOD1_SELECTION_MAX = 99;
const float CUBE_BODY_SELECTION_MAX = 93;
const float CUBE_TAIL_SELECTION_MAX = 98;
const float COLUMN_MIN = 50;
const float COLUMN_MAX = 98;
const uint8_t PREHEAT_POWER = 100;
const uint8_t HEAT_HEADS_POWER = 30;
const uint8_t HEAT_BODY1_POWER = 70;
const uint8_t HEAT_BODY2_POWER = 60;
const uint8_t HEAT_WAITING_POWER = 20;

const int SEND_TIME_PERIOD = 1000;

const uint8_t SelectedItemCount = 4;
enum SelectedItem : uint8_t
{
	sel_power = 0,
	sel_cubeTempConf,
	sel_ColumnTempConf,
	sel_mode
};

const uint8_t mainWorkModeCount = 11;
enum mainWorkMode : uint8_t
{
	wm_off = 0,				//__OFF__
	wm_first,					// 1 WORK
	wm_firstHeating,		// 1 HEAT
	wm_second,				// 2 WORK
	wm_secondHeating,	// 2 HEAT`
	wm_secondGetHeads,	// HEADS_
	wm_secondGetBody,	// _BODY_
	wm_secondsGetTail,	// _TAIL_
	wm_manual,				// MANUAL
	wm_wating,				// _WAIT_
	wm_over_ok				// _OVER_
};
struct State
{///*** добавить в вывод в уарт
	float cubeTemp = 0;
	float stableCubeTemp = 0; ///***
	float stopGetHeadsTemp = 0;///***
	float columnTemp = 0;
	float stableColumnTemp = 0;///***
	float cubeTempConfigured = 80;
	float columnTempConfigured = 70;
	uint8_t power;
	RTC_TimeTypeDef time;
	RTC_TimeTypeDef timeCurrentMode;
	mainWorkMode mode;
};


#ifdef __cplusplus
extern "C" {
#endif
void init();
void loop();
void delay(int ms);


#ifdef __cplusplus
}
#endif

void workTick(void);
uint32_t getEncoderMoves();
uint32_t timeDefTumin(RTC_TimeTypeDef * time);
void mainMenuheat1(void);
void mainMenuheat2(void);
void mainMenuMode1(void);
void mainMenuMode2(void);
void mainMenuManual(void);
void mainMenuExit(void);
void setWaitMode(void);
void setOver(void);
void setStop(void);
uint8_t findAlcoholPercentByTemp(float);
float findTempByAlcohol(uint8_t);


#endif /* INC_MAINCPP_H_ */
