#include <string.h>
#include "Game.h"
#define SAVE 1
#define LOAD 2
#define LOAD_S 3

int readArguments(int argc, char** argv);

void main(int argc, char** argv)
{
	int arg = readArguments(argc, argv);

	Game newGame;
	newGame.startGame(arg);
}

int readArguments(int argc, char** argv)
{
	int i, res = 0;

	for (i = 1; i < argc; i++)
	{
		if (strcmp(argv[i], "-save") == 0)
			res = SAVE;
		else if (strcmp(argv[i], "-load") == 0)
			res = LOAD;
		else if (strcmp(argv[i], "-silent") == 0 && res == LOAD)
			res = LOAD_S;
	}

	return res;
}