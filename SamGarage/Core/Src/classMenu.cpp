/*
 * classMenu.cpp
 *
 *  Created on: Jun 22, 2022
 *      Author: Drey
 */

#include "classMenu.h"
#include "ssd1306.h"
extern int encCounter;
extern Encoder encoder;
extern Button encoderButton;
const FontDef font = Font_7x10;

namespace Menuu {



Menu::Menu()
{
	_itemsCount = 0;
	_selctedItem = 0;
	_lastItem = 0;

}

void Menu::init(item *itemsArray, uint8_t itemsCount)
{
	items = itemsArray;
	_itemsCount = itemsCount;
	_selctedItem = 0;
	runCallback = items[0].call;
	_lastItem = _itemsCount -1;
}

Menu::~Menu() {
	// TODO Auto-generated destructor stub
}

void Menu::nextItem()
{
	if (++_selctedItem >= _itemsCount)
	{
		_selctedItem = 0;
	}
	runCallback = items[_selctedItem].call;
}

void Menu::prevItem()
{
	if (_selctedItem == 0)
	{
		_selctedItem = _itemsCount - 1;
	}
	else _selctedItem--;
	runCallback = items[_selctedItem].call;
}

item Menu::getSelectedItem()
{
	return items[_selctedItem];
}

uint8_t Menu::getSelectedItemId()
{
	return _selctedItem;
}

void Menu::run()
{
	updateScreen();
	bool loop = true;
	while(loop)
	{
		encoder.tick(&encCounter);
		if (encoder.available())
		{
			if (encoder.isRight()) nextItem();
			if (encoder.isLeft()) prevItem();
			updateScreen();
		}
		if (encoderButton.tick() == state_click)
		{
			if (items[_selctedItem].index == indexExit) loop = false;
			if (runCallback != nullptr) runCallback();
			loop = false;
		}
	}
}

void Menu::updateScreen()
{
	ssd1306_Fill(Black);
	const uint8_t fontHeight = 12;
	const uint8_t xSel = 0, xName = 20;
	uint8_t y = 0;
	int i = 0;
	if (_selctedItem >= 5 ) i = _selctedItem -4;
	for ( ; i < _itemsCount; i ++)
	{
		if ( i == _selctedItem)
		{
			ssd1306_SetCursor(xSel, y);
			ssd1306_WriteChar('#', font, White);
		}
		ssd1306_SetCursor(xName, y);
		ssd1306_WriteString(items[i].name, font, White);
		y += fontHeight;
		if (y > 59) break;
	}
	ssd1306_UpdateScreen();
}


} /* namespace Menu */
