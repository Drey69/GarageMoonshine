/*
 * classTimerMillis.cpp
 *
 *  Created on: Mar 13, 2021
 *      Author: 123
 */

#include "classTimerMillis.h"

TimerMillis::TimerMillis(uint32_t time2wait) {
	// TODO Auto-generated constructor stub
	delay_time = time2wait;
	last_time = HAL_GetTick();
}

TimerMillis::TimerMillis() {
}

bool TimerMillis::check()
{
	uint32_t nowT = HAL_GetTick();
	if (last_time + delay_time <= nowT)
	{
		last_time = nowT;
		return true;
	}
	return false;
}

