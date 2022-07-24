/*
 * SenderUart.h
 *messaage content
 * <000.00,000.00,000.00,000.00,mm,ppp,tt.tt.tt>

 *1 = температура колонны с датчика
 *2 =  темп колонны настроенная
 *3 - тем куба с дачика
 *4 = темп куба  настроеная
 *m = режим
 *ppp = мощность
 *tt = время работы режима
 * <> начало и конец сообщения
 *	всего 45 баййт
 *
 *  Created on: Jul 14, 2022
 *      Author: AnderyP
 */

#ifndef SENDERUART_H_
#define SENDERUART_H_
#include "mainCpp.h"
#include "main.h"


#ifdef __cplusplus
extern "C" {
#endif
#include "stdlib.h"
#ifdef __cplusplus
}
#endif

static const uint8_t MessageLength = 45;
class SenderUart {
public:
	SenderUart();
	virtual ~SenderUart();
	void sendStatus(State & st);
private:

	char messageStr[MessageLength] = {0, };
	const uint8_t pos_t1l= 1, pos_t1n = 8; //позиции температур в массиве
	const uint8_t pos_t2l = 15, pos_t2n = 22;
	const uint8_t pos_mode = 29, pos_power = 32;
	const uint8_t pos_time1 = 36;


	void clearStr(void);
	void floatToStr(char *str, const float t);
	void convertStatus(State & st);
	void timeToStr(char *str, RTC_TimeTypeDef & time);

};



#endif /* SENDERUART_H_ */
