#ifndef __MENU_H
#define __MENU_H
#define TRUE 1
#define FALSE 0
#define REGULAR 0
#define COLORED 1
#define OPTION_ONE 1
#define OPTION_TWO 2
#define OPTION_THREE 3
#define OPTION_FOUR 4
#define OPTION_EIGTH 8
#define OPTION_NINE 9
#include <iostream>
#include <windows.h>
using namespace std;

class Menu
{
public:
	Menu();
	~Menu();
	const int printMenu(string& name, int& color, int& difficulty);
	const int printInstructions();
	const void printMenuOptions();
	const string enterScreen();
	const int printColorToggle(int color);
	const int printDifficultyToggle();

};

#endif // __MENU_H