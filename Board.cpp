#include "Board.h"

Board::Board()
{
	this->board = nullptr;
	this->numOfGhosts = 0;
	this->numOfCrumbs = 0;
	this->fruit = Fruit();
};

Board::~Board() {};

void Board::createBoardFromFile(string fileName)
/*this function creates a game board from a file*/
{
	ifstream myBoard(fileName, ios::in);
	string line;

	int height, lengthTotal;
	int lines = 0;
	int ghosts = 0;
	int wallLines = 0;
	int i, j, k, l;
	bool widthFlag = false;

	while (getline(myBoard, line))
		lines++;


	myBoard.clear();
	myBoard.seekg(0);
	this->board = new string[lines];

	for (i = 0; i < lines; i++)
	{
		getline(myBoard, line);
		this->board[i] = line;
	}

	this->height = lines;

	myBoard.close();

	for (i = 0; i < lines; i++)
	{
		for (j = 0; j < this->board[i].length(); j++)
		{
			if (!widthFlag)
			{
				if (this->board[i][j] == '#')
				{
					this->width = this->board[i].length();
					this->bOrigin = Position(i, j);
					widthFlag = true;
				}
			}

			if (this->board[i][j] == '&')
			{
				this->lifeScorePos = Position(i, j);
				for (k = 0; k < 3; k++)
				{
					for (l = 0; l < 20; l++)
					{
						if (this->board[i + k].length() - j <= l)
							this->board[i + k].append(1, '%');
						else
							this->board[i + k][j + l] = '%';
					}
				}
			}

			if (this->board[i][j] == ' ')
			{
				this->emptyPos.push_back(Position(i, j));
				this->board[i][j] = BREAD_CRUMB;
				this->numOfCrumbs++;
			}

			if (this->board[i][j] == '%')
				this->board[i][j] = ' ';

			if (this->board[i][j] == '$')
			{
				this->board[i][j] = BREAD_CRUMB;
				this->numOfCrumbs++;
				this->ghosts[this->numOfGhosts].setObjectPosition(i, j);
				this->ghosts[this->numOfGhosts].setSpawn(i, j);
				this->ghosts[this->numOfGhosts].setColor(numOfGhosts);
				this->numOfGhosts++;
			}

			if (this->board[i][j] == '@')
			{
				this->board[i][j] = ' ';
				this->pac.setObjectPosition(i, j);
				this->pac.setSpawn(i, j);
			}

		}
		if (this->board[i][0] == '#')
			wallLines++;
	}
	this->bEnd = Position(wallLines, width - 1);
}

void Board::drawBoard(int mode)
/*this function is for printing the board to the screen according to the user choice (colored\ uncolored)*/
{
	for (int i = 0; i < this->height; i++)
	{
		for (int j = 0; j < this->width; j++)
		{
			if (board[i][j] == '#')
			{
				colorText(mode, 1 + 1 * 16); // light blue + blue background
				cout << this->board[i][j];
			}
			else if (board[i][j] == ' ')
			{
				colorText(mode);
				cout << this->board[i][j];
			}
			else if (board[i][j] == '@')
			{
				colorText(mode, 6); // yellow
				cout << this->board[i][j];
			}
			else if (board[i][j] == 250)
			{
				colorText(mode);
				cout << this->board[i][j];
			}
			else
			{
				colorText(mode); // default
				cout << this->board[i][j];
			}
		}
		cout << endl;
	}
	colorText(mode);
}

const char Board::getCharFromBoard(const int x, const int y)
{
	return this->board[x][y];
}

void Board::setCharToBoard(const int x, const int y, char toSet)
{
	this->board[x][y] = toSet;
}

Pacman& Board::getPac()
{
	return this->pac;
}

Ghost& Board::getGhost(int ghostID)
{
	return this->ghosts[ghostID];
}

Fruit& Board::getFruit()
{
	return this->fruit;
}

const int Board::getHeight()
{
	return this->height;
}

const int Board::getWidth()
{
	return this->width;
}

const int Board::getNumOfGhosts()
{
	return this->numOfGhosts;
}

const int Board::getNumOfCrumbs()
{
	return this->numOfCrumbs;
}

void Board::setNumOfCrumbs(const int num)
{
	this->numOfCrumbs = num;
}

Position Board::getLifeScorePos()
{
	return this->lifeScorePos;
}

Position Board::getbOrigin()
{
	return this->bOrigin;
}

Position Board::getbEnd()
{
	return this->bEnd;
}

vector<Position> Board::getEmptyPos()
{
	return this->emptyPos;
}

bool Board::checkMove(Cord xPos, Cord yPos, bool isPac)
/*this function checks if the move is legal*/
{
	if (isPac)
	{
		if (yPos < 0 || xPos < 0 || xPos >= height || yPos >= width)
			return false;
		else if (board[xPos][yPos] == '#' || yPos == bOrigin.getY() - 1 || yPos == bEnd.getY() + 1 || xPos == bOrigin.getX() - 1 || xPos == bEnd.getX() + 1)
			return false;
		else
			return true;
	}
	else
	{
		if (board[xPos][yPos] == '#' || yPos == bOrigin.getY() || yPos == bEnd.getY() || xPos == bOrigin.getX() || xPos == bEnd.getX())
			return false;
		else
			return true;
	}
}

void Board::colorText(bool isColor, int color)
/*this function is responsible of printing in color*/
{
	if (isColor)
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
	else
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
}

string* Board::getBoardString()
{
	return this->board;
}