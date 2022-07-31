/*
 * Ten.h
 *
 *  Created on: Jun 8, 2022
 *      Author: Drey
 */

#ifndef INC_TEN_H_
#define INC_TEN_H_
#include "stm32f1xx_hal.h"
#include "mainCpp.h"
#include "main.h"

extern TIM_HandleTypeDef htim3;
extern State status;
class Ten {
public:
	//const uint32_t timePWM = 25000; 	//5 сек для шима
	const uint32_t timePWM = 5000; 	//1 сек для шима
	Ten();
	void init();
	//void tick();
	void setPower(uint32_t power);
	uint32_t getPower();
	void start(uint32_t pow = 50);
	void start();
	void stop();
	bool isEnabled();


private:
	uint32_t powerP;							//процент мощности
	uint32_t pwmPulseTime;
	bool enabled;

	void convertPowerToPwmTime();
};

#endif /* INC_TEN_H_ */
