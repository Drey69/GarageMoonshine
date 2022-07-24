/*
 * Ten.cpp
 *
 *  Created on: Jun 8, 2022
 *      Author: Drey
 */

#include <Ten.h>


Ten::Ten() {
}

void Ten::init()
{
	pwmPulseTime = 0;
	enabled = false;
}


	//HAL_TIM_PWM_Start_IT(&htim1, TIM_CHANNEL_1);
	//все через таймер3 настроен в 50 000 тиков на 10 сек


void Ten::setPower(uint32_t power)
{
	if ( powerP == power ) return;
	powerP = power;
	convertPowerToPwmTime();
	TIM3->CCR1 = pwmPulseTime;
}

uint32_t Ten::getPower() { return powerP; }

void Ten::start(uint32_t pow)
{
	enabled = true;
	setPower(pow);
	HAL_TIM_PWM_Start_IT(&htim3, TIM_CHANNEL_1);
	TIM3->CCR1 = pwmPulseTime;
}

void Ten::stop()
{
	enabled = false;
	HAL_TIM_PWM_Stop_IT(&htim3, TIM_CHANNEL_1);
}

bool Ten::isEnabled() { return enabled; }

void Ten::start()
{
	enabled = true;
	convertPowerToPwmTime();
	HAL_TIM_PWM_Start_IT(&htim3, TIM_CHANNEL_1);
	TIM3->CCR1 = pwmPulseTime;
}

void Ten::convertPowerToPwmTime()
{
	pwmPulseTime = timePWM / 100 * powerP;

}
