/*
 * externs.h
 *
 *  Created on: Mar 1, 2021
 *      Author: Lomaster
 *      timer 4  work for encoder
 *      timer 9  work for ds18b20 delays 	1 000 000 ticks per 1 sec
 *      timer 10 in irq handler starting adc whith dma 50 ticks per sec
 *      timer 2  pwm screen brightness,	pwm freq 1 mhz
 *      timer 11 servo pwm channel 1
 *      timer 3 chanel 4 pwm not  using now
 *		TIMER 5 PWM LED LINE
 */

#ifndef INC_EXTERNS_H_
#define INC_EXTERNS_H_


#include "main.h"
#include "stdbool.h"

typedef uint16_t color;
typedef const uint32_t w25Addr;



enum WorkMode
{
	ModeFirst = 25,
	ModeSecond,
	ModePWM,
	ModeStop,
	ModePause,
	ModeFinished,
	ModeError
};
enum ModeSteps
{
	StepHeadSelection = 35,
	StepBodySelection,
	StepTaleSelection,
	StepWarmingUp,
	StepWaiting,
	StepStoped
};
enum WorkSubMode
{
	SubAutoMode = 45,
	SubNormaMode,
	SubError,
	SubStoped,
	SubPaused
};
enum ValveSatus
{
	valveClosed = 55,
	vlaveOpened
};
enum wireStatus
{
	wireLineBusy = 60,
	wireReady,
	wireRomCrcError,
	wireRamCrcError,
	wireRomCrcOk,
	wireRamCrcOk,
	wireNoPresentPulse,
	wireGotPulse
};
enum ds_error
{
	ds_error_crc = 70,
	ds_error_line,
	ds_error_noRespond,
	ds_error_critical,
	ds_ok
};


struct TempState
{
	float SensorTemp;
	float LimitTemp;
	float AlarmTemp;
	float deltaTemp;
	float correctionData;
	uint8_t simpleCorrectionEable;
	uint8_t presureCorrectionEable;
	uint32_t ExceedTime;
	uint32_t limitExceedTime;
};

struct CurrentStatus
{
	enum WorkMode mode;
	enum WorkSubMode submode;
	enum ModeSteps steps;
	enum ValveSatus valve;
	enum wireStatus wire;
	enum ds_error ds_Error;
	struct TempState cubeSenor;
	struct TempState columnSensor;
//	RTC_TimeTypeDef nowTime;
//	RTC_DateTypeDef nowDate;
//	RTC_TimeTypeDef startTime;
	//RTC_DateTypeDef startDate;
};

struct DefaultColors
{
	color timeBgColor;
	color timeFontColor;
	color textFontColor;
	color textBgColor;
	color bottomBgColor;
	color bottomFontColor;
	color BgColor;
	color selectedTextFontColor;
	color selectedTextBgColor;
};

extern TIM_HandleTypeDef htim2;
extern TIM_HandleTypeDef htim4;
extern TIM_HandleTypeDef htim5;
extern TIM_HandleTypeDef htim10;	//start ADC
extern TIM_HandleTypeDef htim11;	//servo
//extern ADC_HandleTypeDef hadc1;
extern DMA_HandleTypeDef hdma_adc1;
//extern RTC_HandleTypeDef hrtc;
extern TIM_HandleTypeDef htim9; // тикает 1 000 000 раз в сек делей для дс18б20

extern volatile bool encoderFlag;
extern volatile bool adcReady;
//extern volatile byte timer10;
extern volatile uint16_t adcval[4];


extern struct DefaultColors defColor;





/*

extern Encoder encoder;
extern Thermistor tColumn;
extern Thermistor tCube;
extern Thermistor sBright;

*/


#define SUPPLY_VOLTAGE 3.3
#define MAX_ADC_BRIGHT 3000
#define MIN_ADC_BRIGHT 10

//  enums 30
#endif /* INC_EXTERNS_H_ */
