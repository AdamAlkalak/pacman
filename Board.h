#pragma once
#ifndef __BOARD_H
#define __BOARD_H
#define _CRT_SECURE_NO_WARNINGS
#define BREAD_CRUMB 250
#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include "Ghost.h"
#include "Pacman.h"
#include "Fruit.h"
using namespace std;

class Board
{
private:
	string* board;
	vector<Position> emptyPos;
	Ghost ghosts[4];
	Pacman pac;
	Fruit fruit;
	Position lifeScorePos, bOrigin, bEnd; // 1st is the location of the &, 2nd is the location of the board [0, 0] position(in case there are spaces above)
	int height, width;
	int numOfGhosts;
	int numOfCrumbs;

public:
	Board();
	~Board();
	void createBoardFromFile(string fileName);
	void drawBoard(int mode = 0);
	const char getCharFromBoard(const int x, const int y);
	void setCharToBoard(const int x, const int y, char toSet);
	Pacman& getPac();
	Ghost& getGhost(int ghostID);
	Fruit& getFruit();
	const int getHeight();
	const int getWidth();
	const int getNumOfGhosts();
	const int getNumOfCrumbs();
	void setNumOfCrumbs(const int num);
	Position getLifeScorePos();
	Position getbOrigin();
	Position getbEnd();
	vector<Position> getEmptyPos();
	bool checkMove(Cord xPos, Cord yPos, bool isPac);
	void colorText(bool isColor, int color = 7);
	string* getBoardString();
	
};

#endif //__BOARD_H