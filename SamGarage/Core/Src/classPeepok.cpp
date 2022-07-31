/*
 * classPeepok.cpp
 *
 *  Created on: 23 июн. 2022 г.
 *      Author: Drey
 */

#include "classPeepok.h"


Pipka::Pipka() {	pinEnabled = false;}
//************************************************************************************************************
void Pipka::playBlocking(Melody melody)
{
	int i = 0;
	int currentTime = HAL_GetTick(), lastTime = currentTime;
	while ( melodySet[melody][i] != -1) //i%2 = 0 пищим 1 не пищим
	{
		if ( i % 2 ) //не пищим
		{
			if ( pinEnabled )
			{
				resetPin();
				lastTime = HAL_GetTick();
			}
			else
			{
				currentTime = HAL_GetTick();
				if (lastTime + melodySet[melody][i] > currentTime) // если время молчания вышло
				{
					i++;
				}
			}
		}
		else // пищим
		{
			if (pinEnabled)
			{
				currentTime = HAL_GetTick();
				if ( lastTime + melodySet[melody][i] > currentTime) //харе пищать ноту
				{
					//resetPin();
					i++;
				}
			}
			else
			{
				setPin();
				lastTime = HAL_GetTick();
			}
		}
	}
	resetPin();
}
//************************************************************************************************************
void Pipka::buttonClickPlay(void) { playBlocking (m_buttonClick); }

void Pipka::encoderTurnPlay(void) { playBlocking (m_encoderTick); }

Pipka::~Pipka() {
	// TODO Auto-generated destructor stub
}

void Pipka::setPin(void)
{
	if ( !pinEnabled )
		{
		HAL_GPIO_WritePin(gpio_port, gpio_pin, GPIO_PIN_SET);
		pinEnabled = true;
		}

}

void Pipka::resetPin(void)
{
	 if ( pinEnabled )
		 {
		 	 HAL_GPIO_WritePin(gpio_port, gpio_pin, GPIO_PIN_RESET);
		 	 pinEnabled = false;
		 }
}

void Pipka::init(GPIO_TypeDef* port, uint16_t pin)
{
	gpio_port = port;
	gpio_pin = pin;
	resetPin();
}

