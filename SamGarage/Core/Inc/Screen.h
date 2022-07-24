/*
 * Screen.h
 *
 *  Created on: Jun 8, 2022
 *      Author: Drey
 */
#include "mainCpp.h"
#include "main.h"

#ifdef __cplusplus
extern "C" {
#endif
#include "stdlib.h"
#ifdef __cplusplus
}
#endif
//
//#include "stdio.h"
//#include "usart_ring.h"
#include "ssd1306.h"
//#include "string.h"
#ifndef SRC_SCREEN_H_
#define SRC_SCREEN_H_
#include "stm32f1xx_hal.h"

//extern State;// status;

struct Pos
{
	uint8_t X;
	uint8_t Y;
	FontDef Font;
} ;

struct rectPos
{
	uint8_t x1;
	uint8_t y1;
	uint8_t x2;
	uint8_t y2;
};

class Screen {

public:
	char* modeNames[11];
	RTC_TimeTypeDef time = {0};
	Screen();
	void clearScreen();
	void init();
	void clearTime();
	void updateScreen();
	void setPower(uint32_t pow);
	void setColumnTemp(float );
	void setCubeTemp(float );
	void setColumnTempConf(float );
	void setCubeTempConf(float );
	void setStatus(State*);
	void setSelItem(uint8_t item);
private://----------------------------------позиции текстов
	const Pos posPower {65, 39, Font_11x18};
	const Pos posTime {1, 39, Font_7x10};
	const Pos posColTemp {83, 0, Font_11x18};
	const Pos posColTempConf {83, 19, Font_11x18};
	const Pos posCubeTemp {1, 0, Font_11x18};
	const Pos posCubeTempConf {1, 19, Font_11x18};
	const Pos posMode {1, 51, Font_7x10};

	const rectPos rectTempCubeConf  {0, 18, 46, 37};
	const rectPos rectTempColConf {82, 18, 127, 37};
	const rectPos rectMode {0, 50, 63, 61};
	const rectPos rectPower {63, 38, 127, 58};

//------------------------------------------------- поицц прямойгольников выделеия

	//const Pos posKvadat = {0, 44, Font_7x10};
	State state;
	uint8_t selItem;
	char strTempCube[7];
	char strTempCubeConf[7];
	char strTempCol[7];
	char strTempColConf[7];

	void timeToStr(char* str);
	void powerToStr(char* str);
	void floatToStr ( char *str, const float t);
	bool changedData;
	void clearArr(char * arr, int len);
	uint32_t millis;

};

#endif /* SRC_SCREEN_H_ */
