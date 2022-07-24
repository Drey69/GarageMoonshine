/*
 * classPeepok.h
 *
 *  Created on: 23 июн. 2022 г.
 *      Author: Drey
 */

#ifndef CLASSPEEPOK_H_
#define CLASSPEEPOK_H_
#include "stm32f1xx_hal.h"
#include "main.h"

const int melodyCountConst = 9;
const int notesCountConst = 10;
enum Melody //музоны должны идти по порядку с массивом ибо через них доступ к нему
{
	m_encoderTick = 0,
	m_buttonClick,
	m_buttonHold,
	m_deviceStart,
	m_changeMode,
	m_temOff,
	m_tenOn,
	m_error,
	m_alarm
};

class Pipka {
public:

	Pipka();
	void init(GPIO_TypeDef *, uint16_t);
	void playBlocking(Melody melody);
	void buttonClickPlay(void);
	void encoderTurnPlay(void);

	virtual ~Pipka();
private:
	GPIO_TypeDef * gpio_port;
	uint16_t gpio_pin;
	bool pinEnabled;

	void setPin(void);
	void resetPin(void);
	const short melodySet[melodyCountConst][notesCountConst] = //обязательно все кончаются на -1 минус один
	{
			{100, 10, -1,}, //encoder tick
			{150, 50, -1,},//button click
			{200, 50, -1}, // button hold
			{350, 50, 200, 50, 100, 50, 100, 100, -1,}, // start devise
			{200, 50, 200, -1,}, //change mode
			{500, 100, 150, 100, -1,}, //ten off
			{150, 100, 500, 100, -1,}, //tem on
			{350, 100, 350, 100, -1,}, //error
			{400, 200, -1} //alarm
			//добавить коец перегона
	};
};



#endif /* CLASSPEEPOK_H_ */
