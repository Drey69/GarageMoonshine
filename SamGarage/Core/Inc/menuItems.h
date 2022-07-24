/*
 * menuItems.h
 *
 *  Created on: 22 июн. 2022 г.
 *      Author: Drey
 */

#ifndef INC_MENUITEMS_H_
#define INC_MENUITEMS_H_

#include "classMenu.h"
using namespace Menuu;
void mainMenuheat1(void);
void mainMenuheat2(void);
void mainMenuMode1(void);
void mainMenuMode2(void);
void mainMenuManual(void);
void mainMenuExit(void);
void mainMenuGetHead(void);
void mainMenuGetBody(void);
void mainMenuGetTail(void);

item mainMenuItems[] =
{
		{ 0, " HEAT 1 ", mainMenuheat1},
		{ 1, " HEAT 2 ", mainMenuheat2},
		{ 2, " MODE 1 ", mainMenuMode1},
		{ 3, " MODE 2 ", mainMenuMode2},
		{ 4, " MANUAL ", mainMenuManual},
		{ 5, " 2 BODY ", mainMenuGetBody},
		{ 6, " 2 TAIL ", mainMenuGetTail},
		{ 7, " 2 HEAD ", mainMenuGetHead},
		{ 255, " EXIT ", mainMenuExit},
};
const uint8_t mainMenuItemCount = 9;



#endif /* INC_MENUITEMS_H_ */
