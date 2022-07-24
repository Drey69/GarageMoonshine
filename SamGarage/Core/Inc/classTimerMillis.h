/*
 * classTimerMillis.h
 *
 *  Created on: Mar 13, 2021
 *      Author: 123
 */

#ifndef SRC_CLASSTIMERMILLIS_H_
#define SRC_CLASSTIMERMILLIS_H_

#include "stm32f1xx_hal.h"

class TimerMillis
{
private:
	uint32_t delay_time;
	uint32_t last_time;


public:
	TimerMillis(uint32_t);
	TimerMillis();
	bool check();
};

#endif /* SRC_CLASSTIMERMILLIS_H_ */
