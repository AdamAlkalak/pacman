#include "Menu.h"

Menu::Menu() {}
Menu::~Menu() {}

const int Menu::printMenu(string& name, int& color, int& difficulty)
/*this function handles the main menu, and taking care of correct input and colored\uncolored game*/
{
	bool validInput = true;
	int userChoice, flag = TRUE;
	color = REGULAR; // default
	difficulty = 1;

	while (flag)
	{

		system("cls");

		printMenuOptions();

		do 
		{
			cin >> userChoice;
			if (userChoice != OPTION_ONE && userChoice != OPTION_TWO && userChoice != OPTION_THREE && userChoice != OPTION_FOUR && userChoice != OPTION_EIGTH && userChoice != OPTION_NINE && userChoice == 0)
			{
				cout << "INCORRECT INPUT, PLEASE TRY AGAIN:" << endl;

				cin.clear();
				cin.ignore();
				validInput = false;
			}
			else
				validInput = true;
		} while (!validInput);

		switch (userChoice)
		{
		case OPTION_ONE:

			system("cls");
			return OPTION_ONE;
			break;

		case OPTION_TWO:
			color = printColorToggle(color);
			break;

		case OPTION_THREE:
			system("cls");
			name = enterScreen();
			system("cls");
			return OPTION_THREE;
			break;

		case OPTION_FOUR:

			system("cls");
			difficulty = printDifficultyToggle();
			break;

		case OPTION_EIGTH:

			system("cls");
			flag = printInstructions();
			break;

		case OPTION_NINE:

			cout << "GOOD BYE!";
			exit(0);

		default:
			break;
		}
	}

	cout << "GOOD BYE!";
}

const int Menu::printInstructions()
/*this function prints the instruction of the game*/
{
	int flag;

	cout << "YOU HAVE TO EAT ALL THE BREADCRUMBS AND FRUITS WITHOUT BEING EATEN BY THE GHOSTS!" << endl;
	cout << "YOU HAVE ONLY 3 LIVES!" << endl;
	cout << "TO GO LEFT, PRESS A OR a" << endl;
	cout << "TO GO RIGHT, PRESS D OR d" << endl;
	cout << "TO GO UP, PRESS W OR w" << endl;
	cout << "TO GO DOWN, PRESS X OR x" << endl;
	cout << "TO STAY IN PLACE, PRESS S OR s\n" << endl;
	cout << "TO GO BACK TO THE MAIN MENU, PRESS 1" << endl;
	cout << "TO EXIT, PRESS 0" << endl;

	cin >> flag;

	while (flag != FALSE && flag != TRUE)
	{
		cout << "INCORRECT INPUT, PLEASE TRY AGAIN:" << endl;
		cin >> flag;
	}

	return flag;
}

const void Menu::printMenuOptions()
/*this function prints the main menu*/
{
	cout << "WELCOME TO PACMAN!\n" << endl;
	cout << "(1) START A NEW GAME" << endl;
	cout << "(2) TOGGLE COLOR" << endl;
	cout << "(3) START A NEW GAME ON A SPECIFIC SCREEN" << endl;
	cout << "(4) CHOOSE DIFFICULTY" << endl;
	cout << "(8) PRESENT INSTRUCTIONS AND KEYS" << endl;
	cout << "(9) EXIT" << endl;
}

const string Menu::enterScreen()
{
	string name;
	cout << "Enter file name of your desired screen: " << endl;
	cin >> name;

	return name;
}

const int Menu::printColorToggle(int color)
{
	if (color == REGULAR)
	{
		cout << "COLOR MODE ON!\n" << endl;
		Sleep(500);
		return COLORED;
	}
	else if (color == COLORED)
	{
		cout << "COLOR MODE OFF!\n" << endl;
		Sleep(500);
		return REGULAR;
	}
}

const int Menu::printDifficultyToggle()
{
	int choice = -1;

	cout << "GAME DIFFICULTY MODES:" << endl;
	cout << "NOICE(DEFAULT) - GHOSTS ROAM AROUND THE MAP RANDOMLY, THEY DON'T REALLY CARE ABOUT YOU." << endl;
	cout << "GOOD - THE GHOSTS ARE ON THE HUNT FOR YOUR HEAD, BUT OCCASIONALLY THEIR MIND WANDERS." << endl;
	cout << "BEST - THESE GHOSTS ARE TRAINED ASSASSINS, THEY WON'T REST UNTIL YOU MEET YOUR END" << endl;
	cout << endl;
	cout << endl;
	cout << endl;
	cout << "FOR NOVICE PRESS 1" << endl;
	cout << "FOR GOOD PRESS 2" << endl;
	cout << "FOR BEST PRESS 3" << endl;


	cin >> choice;

	while (choice != 1 && choice != 2 && choice != 3)
	{
		cout << "INCORRECT INPUT, PLEASE TRY AGAIN:" << endl;
		cin >> choice;
	}

	return choice;
}