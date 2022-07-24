/*
 * StartMenu.h
 *
 *  Created on: 18 июн. 2022 г.
 *      Author: AnderyP
 */

#ifndef INC_STARTMENU_H_
#define INC_STARTMENU_H_
struct menuItem
{
	int index;
	char name[15];
	void(* foo)(int index);
};
class StartMenu {
public:
	int selectedItemIndex;
	StartMenu();
	StartMenu(int count);
	void addItem(menuItem m);
	void show();
	virtual ~StartMenu();
};

#endif /* INC_STARTMENU_H_ */