/*
 * button.h
 *
 *  Created on: 29 июн. 2020 г.
 *      Author: 123
 */

#ifndef SRC_BUTTON_H_
#define SRC_BUTTON_H_

#define state_push 0
#define state_free 1
#define state_pushed 2
#define state_first_click 99
#define state_click 100
#define state_dodle_click 102
#define state_hold 200
#define push_time 2000 			/// millisec
//#define debuounce_time 20 		// millisec
//#define between_click_time 300 	// millisec inside now

#include "stm32f1xx_hal.h"

class Button
	{
	private:
		uint32_t lastTime, time, now_time, last_click_time;
		uint8_t lastState, click_count, nowState = state_free;
		uint8_t button_state, return_value, contact_bounce;
		GPIO_TypeDef * gpio_port;
		uint16_t gpio_pin, between_click_time;

	public:
		Button (){};
		Button (GPIO_TypeDef * bport, uint16_t bpin, uint8_t bounce = 15, uint16_t between_dclick_time = 500)
				{
					gpio_port = bport;
					gpio_pin = bpin;
					contact_bounce = bounce;
					between_click_time = between_dclick_time;
					return_value = 0;
					now_time = HAL_GetTick();
					last_click_time = now_time;
					button_state = HAL_GPIO_ReadPin(gpio_port, gpio_pin);
					//click_count = 0;
				}
		uint8_t tick ();

		void set_between_click_time(uint16_t bci);

		void set_debounce_time(uint8_t db);

		uint8_t isButtonClicked();
		uint8_t isButtonHolded();
		uint8_t getButtonState();
		void clearButtonState();

	};


#endif /* SRC_BUTTON_H_ */
