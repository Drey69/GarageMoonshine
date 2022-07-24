/*
 * button.cpp
 *
 *  Created on: 29 июн. 2020 г.
 *      Author: 123
 */

#include "classButton.h"

uint8_t Button::tick()
{
	return_value = state_free;
	now_time = HAL_GetTick();
	time = now_time - lastTime;
	button_state = HAL_GPIO_ReadPin(gpio_port, gpio_pin);

	if (button_state == state_free) {
		if (lastState == state_free) {
			//lastTime = nowTime;
			//ret = 0;
		} else {
			if (time <= contact_bounce) { // если дребезг или помеха
				//lastTime = nowTime;
				lastState = state_free;
			} else if (time > contact_bounce) {
				lastState = state_free;
				return_value = state_click;
				//lastTime = nowTime;
				//return state_hold;
			}
			if (time > push_time) {
				lastState = state_free;
				//lastTime = nowTime;
				return_value = state_hold;
			}
		}
	} else {
		if (lastState == state_free) {
			lastState = state_push;
			lastTime = now_time;
			return_value = state_pushed;
		} else {

		}
	}
	if (return_value == state_click)					// дабле килкен будет?
	{
		if ((last_click_time + between_click_time) < now_time) {
			//невложились в время для даблклика
			last_click_time = now_time;
		} else {	// вложились
			last_click_time = now_time - between_click_time;
			return_value = state_dodle_click;
			//
		}
	}
	if (nowState == state_free) nowState = return_value;
	return return_value;
}

void Button::set_between_click_time(uint16_t bci)
{
	between_click_time = bci;
}

void Button::set_debounce_time(uint8_t db)
{
	contact_bounce = db;
}

uint8_t Button::isButtonClicked()
{
	if (nowState == state_click)
		{
			nowState = state_free;
			return 1;
		}
	nowState = state_free;
	return 0;
}

uint8_t Button::isButtonHolded()
{
	if (nowState == state_hold)
		{
			nowState = state_free;
			return 1;
		}
	nowState = state_free;
	return 0;
}

uint8_t Button::getButtonState()
{
	return nowState;
}

void Button::clearButtonState() {
	nowState = state_free;
}
