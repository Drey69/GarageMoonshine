
/*
 * 		Lomaster code style encoder driver    ******************
 *
 * 		configure your timer to encoder mode, enable global timer interrupts
 * 		in main() before while(true){}
 * 		change you htim on your timer and your chanel.
 * 		run timer example HAL_TIM_Encoder_Start_IT(&htim4, TIM_CHANNEL_1);
 * 		copy callback and change TIM4 on your TIMx
 * 		void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim) // прерывание по енкодеру
 *		{
 *       	if(htim->Instance == TIM4)
 *       	{
 *       		if (__HAL_TIM_IS_TIM_COUNTING_DOWN(&htim4)) encCounter--;
 *       		else encCounter++;
 *       	}
 *		}
 */

#include "classEncoder.h"


extern volatile bool encoderFlag;

//-----------------------------------CTOR---------------------------------------------------------------
Encoder::Encoder()
{
	counts = 0;
	turned = 0;
}
//-----------------------------------PUBLIC-------------------------------------------------------------

void Encoder::tick(int *tick) 	// входящий параметр скольько щелчков накрутили енкодеру
{
	int temp = *tick;
	*tick = 0;
	if (temp) turned = true;
	counts += temp;
	}
//------------------------------------------------------------------------------------------------------

bool Encoder::available()		// отдает true если крутили и есть чего считать
{
	return turned;
}
//------------------------------------------------------------------------------------------------------

int Encoder::getOneStep() 		// выдает +1 или -1 зависит от направления и уменьшает количество накрыченых counts
{
	if (counts > 0)
	{
		--counts;
		if (!counts) turned = false;
		return 1;
	}
	if (counts < 0)
	{
		++counts;
		if (!counts) turned = false;
		return -1;
	}
	return 0;
}
//------------------------------------------------------------------------------------------------------

bool Encoder::isLeft()			// было ли крутнуто в лево
{
	bool rez = false;
	if (counts < 0)
	{
		rez = true;
		counts++;
	}
	if (!counts) turned = false;
	return rez;
}
//------------------------------------------------------------------------------------------------------

bool Encoder::isRight()			// было ли крутнуто в право
{
	bool rez = false;
	if (counts > 0)
	{
		rez = true;
		counts--;
	}
	if (!counts) turned = false;
	return rez;
}
//------------------------------------------------------------------------------------------------------

int Encoder::getAllSteps()		//получить все шаги
{
	int temp = counts;
	counts = 0;
	turned = false;
	return temp;
}
//------------------------------------------------------------------------------------------------------

void Encoder::clearSteps(void) 	// очистить все щелчки что накрутились
{
	counts = 0;
	turned = false;
}
//------------------------------------------------------------------------------------------------------







