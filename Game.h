#ifndef __GAME_H
#define __GAME_H
#define ESC 27
#define DEFAULT_LIFE 3
#define RESET_SCORE 0
#define WIN 1
#define LOSE 0
#define NOVICE 1
#define GOOD 2
#define LOAD 2
#include <conio.h>
#include <windows.h>
#include <iostream>
#include <filesystem>
#include <vector>
#include <queue>
#include "Pacman.h"
#include "Ghost.h"
#include "Fruit.h"
#include "Menu.h"
#include "Board.h"
using namespace std;
namespace fs = std::filesystem;

/*this class is responsible for the logic of the game and the board*/
struct dPos {
	Position pos;
	int distance;
};

struct chint {
	int len;
	char dir;
};

class Game
{
public:
	Game();
	~Game();
	void startGame(int arg);
	int getLife();
	int getScore();
	void setLife(int newLife);
	void setScore(int newScore);
	bool gameOperator(int mode, int difficulty, int arg, ofstream& stepsFile, ofstream& resultFile);
	void gotoxy(int x, int y);
	void movePac(Pacman& pacman, Cord& pacX, Cord& pacY, char& direction, int mode);

	template <class Creature>
	void moveCreature(Creature& creature, int num, int mode);
	void smartGhost(Ghost& ghost, Pacman& pac, int mode);
	int bestPathLen(Cord ghostX, Cord ghostY, Pacman& pac);
	void pausingLoop();
	void printScoreAndLives(int mode);
	void printPausingMessage(int mode);
	bool isEaten(Pacman& pacman, Cord& pacX, Cord& pacY, int& fruitIterator);
	vector<string> loadFile(int& numOfFiles);
	void printWinLoseMessage(int flag);
	void handleButtonPress(char& direction, Pacman& pacman, int mode);
	void loadGameFromFile(string screenName, int arg);
	int strToInt(string str);

private:
	int life;
	int score;
	Board board;
};

#endif // __GAME_H