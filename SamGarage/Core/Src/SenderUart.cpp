/*
 * SenderUart.cpp
 *
 *  Created on: Jul 14, 2022
 *      Author: AnderyP
 */

#include "SenderUart.h"
extern UART_HandleTypeDef huart2;


SenderUart::SenderUart() {
	// TODO Auto-generated constructor stub

}

SenderUart::~SenderUart() {
	// TODO Auto-generated destructor stub
}

void SenderUart::sendStatus(State &st)
{
	clearStr();
	convertStatus(st);
	HAL_UART_Transmit_DMA(&huart2, (uint8_t*)messageStr, MessageLength);
}

void SenderUart::floatToStr(char *str, const float t)
{
	int tempT = t * 100;
	str[0] = '0';
	if (t < 100) str++;
	itoa ( tempT/100, str, 10);
	if (t >= 100) str += 3;
	else str += 2;
	*str = '.';
	str++;
	tempT = tempT % 100;
	if (tempT < 10)
	{
		str[0] = '0';
		str++;
	}
	itoa ( tempT, str, 10);
}

void SenderUart::clearStr(void)
{
	for ( int i = 0; i < MessageLength; i++)
	{
		messageStr[i] = '0';
	}
}

void SenderUart::convertStatus(State & st)
{
	messageStr[0] = '<';						//начало сообщения
	floatToStr(&(messageStr[pos_t1l]),  st.columnTemp);
	messageStr[pos_t1n -1] = ',';
	floatToStr(&(messageStr[pos_t1n]),  st.columnTempConfigured);
	messageStr[pos_t2l -1] = ',';
	floatToStr(&(messageStr[pos_t2l]),  st.cubeTemp);
	messageStr[pos_t2n -1] = ',';
	floatToStr(&(messageStr[pos_t2n]),  st.cubeTempConfigured);
	messageStr[pos_mode -1] = ',';
	if (st.mode < 10)
		{
		messageStr[pos_mode] = '0';
		itoa(st.mode, &(messageStr[pos_mode+1]), 10);
		}
	else
		itoa(st.mode, &(messageStr[pos_mode]), 10);
	messageStr[pos_power - 1] = ',';
	if (st.power < 100)
	{
		messageStr[pos_power] = '0';
		itoa(st.power, &(messageStr[pos_power+1]), 10);
	}
	else
		itoa(st.power, &(messageStr[pos_power]), 10);
	messageStr[	pos_time1 -1] = ',';
	timeToStr(&(messageStr[pos_time1]), st.time);
	messageStr[MessageLength-1] = '>';
}

void SenderUart::timeToStr(char *str, RTC_TimeTypeDef & time)
{
	char digit[3];
	itoa(time.Hours, digit, 10);
	if (time.Hours < 10)
	{
		str[0] = '0';
		str[1] = digit[0];
	}
	else {
		str[0] = digit[0];
		str[1] = digit[1];
	}
	str[2] = '.';
	itoa(time.Minutes, digit, 10);
	if (time.Minutes < 10)
	{
		str[3] = '0';
		str[4] = digit[0];
	}
	else {
		str[3] = digit[0];
		str[4] = digit[1];
	}
	str[5] = '.';
	itoa(time.Seconds, digit, 10);
		if (time.Seconds < 10)
		{
			str[6] = '0';
			str[7] = digit[0];
		}
		else {
			str[6] = digit[0];
			str[7] = digit[1];
		}
		str[8] = 0;
}

uint8_t SenderUart::checkMessage(void)
{
//	if ( !uart_available()) return;
}
