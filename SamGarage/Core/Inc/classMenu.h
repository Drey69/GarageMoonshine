/*
 * classMenu.h
 *
 *  Created on: Jun 22, 2022
 *      Author: Drey
 */

#ifndef CLASSMENU_H_
#define CLASSMENU_H_
#include "stm32f1xx_hal.h"
#include "ssd1306.h"
#include "classEncoder.h"
#include "classButton.h"


namespace Menuu {
using namespace std;

//extern int encCounter;
//extern Encoder encoder;
//extern Button encoderButton;

const uint8_t indexExit = 255;
struct item
{
	uint8_t index;		//идекс 255 тольк у меню выхода exit
	char name[16];
	void (* call)(void); //указатель на фуекцию обработки тыка на меню
};

class Menu {
public:
	Menu();
	void init(item* itemsArray, uint8_t itemsCount);
	virtual ~Menu();
	void nextItem();
	void prevItem();
	item getSelectedItem();
	uint8_t getSelectedItemId();
	void run();


private:

	const uint8_t lineSizeY= 12;
	item* items;
	uint8_t _itemsCount;
	uint8_t _selctedItem;
	uint8_t _lastItem;
	void (*runCallback)(void);
	void updateScreen();

};

} /* namespace Menu */

#endif /* CLASSMENU_H_ */
