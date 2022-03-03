#include "Game.h"

Game::Game()
{
	life = 3;
	score = 0;
}
Game::~Game() {}

void Game::startGame(int arg)
/*this function calls the menu function, and the board creation function*/
{
	int choice, numOfScreens, color, i, difficulty;
	bool loseFlag = false;
	Menu menu;
	string fileName, chosenScreen, stepsName, resultName, numOfGhostStr = "0";
	vector<string> screens;
	ofstream stepsFile, resultFile;

	screens = loadFile(numOfScreens);
	if (arg == 0 || arg == 1)
		choice = menu.printMenu(chosenScreen, color, difficulty);

	switch (arg)
	{
	case 0:
		if (choice == OPTION_ONE)
		{
			for (i = 0; i < numOfScreens; i++)
			{
				system("cls");
				this->board.createBoardFromFile(screens[i]);

				if (!loseFlag)
					loseFlag = gameOperator(color, difficulty, arg, stepsFile, resultFile);
				else
					break;

				delete[] this->board.getBoardString();
				this->board = Board();
			}

			if (!loseFlag)
				printWinLoseMessage(WIN);

		}
		else if (choice == OPTION_THREE)
		{
			system("cls");
			for (i = 0; i < numOfScreens; i++)
			{
				size_t locate = screens[i].find(chosenScreen);
				if (locate != string::npos)
				{
					this->board.createBoardFromFile(screens[i]);
					break;
				}
				else if (i == numOfScreens - 1)
				{
					cout << "This screen doesn't exit in directory, perhaps you had a typo?.... GOOD BYE!" << endl;
					exit(0);
				}
			}

			loseFlag = gameOperator(color, difficulty, arg, stepsFile, resultFile);

			if (!loseFlag)
				printWinLoseMessage(WIN);

			delete[] this->board.getBoardString();
			this->board = Board();
		}

		break;
	case 1:
		for (i = 0; i < numOfScreens; i++)
		{
			system("cls");
			this->board.createBoardFromFile(screens[i]);

			if (!loseFlag)
			{
				string screenName;
				screenName = screens[i];

				stepsName = screenName.erase(screens[i].size() - 11, screens[i].size()); stepsName.append(".steps");
				resultName = screenName; resultName.append(".result");
				stepsFile.open(stepsName, ios::out);
				resultFile.open(resultName, ios::out);

				numOfGhostStr[0] += board.getNumOfGhosts();
				stepsFile << numOfGhostStr << endl;

				loseFlag = gameOperator(color, difficulty, arg, stepsFile, resultFile);

				stepsFile.close();
				resultFile.close();
			}
			else
				break;



			delete[] this->board.getBoardString();
			this->board = Board();
			numOfGhostStr = "0";
		}

		if (!loseFlag)
			printWinLoseMessage(WIN);

		break;
	case 2: case 3:
		for (i = 0; i < numOfScreens; i++)
		{
			system("cls");
			this->board.createBoardFromFile(screens[i]);
			loadGameFromFile(screens[i], arg);

			delete[] this->board.getBoardString();
			this->board = Board();
		}
		break;

	default:
		break;
	}



	screens.erase(screens.begin(), screens.end());
}

int Game::getLife()
{
	return this->life;
}

int Game::getScore()
{
	return this->score;
}

void Game::setLife(int newLife)
{
	this->life = newLife;
}

void Game::setScore(int newScore)
{
	this->score = newScore;
}

bool Game::gameOperator(int mode, int difficulty, int arg, ofstream& stepsFile, ofstream& resultFile)
/*this function operates the game, each part of it will be described sepperatly*/
{
	int iterator = 1;
	int ghostIterator = 0;
	int fruitIterator = 1;
	int score = 0;

	bool winFlag = false;
	bool loseFlag = false;
	bool dizzyGhostsFlag = false;
	bool deathFlag = false;

	char key = 0;
	char direction = 'S';
	char breadCrumb = 250;

	Pacman& pacman = this->board.getPac();
	Fruit& fruit = board.getFruit();
	Cord pacX = this->board.getPac().getObjectPositionX();
	Cord pacY = this->board.getPac().getObjectPositionY();

	this->board.drawBoard(mode); /*drawing the board*/

	while (!winFlag && !loseFlag) /*the main loop of the of the game, it stops in a win case or a lose case*/
	{

		movePac(pacman, pacX, pacY, direction, mode); /*moving the pacman*/
		Sleep(150);

		stepsFile << pacman.getDirection() << " ";
		if (iterator % 2 == 0)
		{
			for (int i = 0; i < this->board.getNumOfGhosts(); i++)
				stepsFile << this->board.getGhost(i).getDirection() << " ";
		}
		else
		{
			for (int i = 0; i < this->board.getNumOfGhosts(); i++)
				stepsFile << "*" << " ";
		}
		if (fruit.getSpawnVal())
		{
			stepsFile << this->board.getFruit().getDirection() << " ";
			stepsFile << this->board.getFruit().getObjectPositionX() << "," << this->board.getFruit().getObjectPositionY() << " ";
			stepsFile << this->board.getFruit().getIcon() << " ";
		}
		else
			stepsFile << "*" << " ";

		stepsFile << endl;

		deathFlag = isEaten(pacman, pacX, pacY, fruitIterator); /*cheking if the pacman has been eaten by the ghosts*/

		if (difficulty == NOVICE)
		{
			if (iterator % 2 == 0)
				for (int i = 0; i < this->board.getNumOfGhosts(); i++) /*moving the ghosts*/
					moveCreature(this->board.getGhost(i), i + 1, mode);
		}

		else if (difficulty == GOOD)
		{
			if (iterator % 20 == 0)
				dizzyGhostsFlag = true;

			if (dizzyGhostsFlag)
			{
				if (ghostIterator != 5)
				{
					for (int i = 0; i < this->board.getNumOfGhosts(); i++) /*moving the ghosts*/
						moveCreature(this->board.getGhost(i), i + 1, mode);

					ghostIterator++;
				}

				else
				{
					ghostIterator = 0;
					dizzyGhostsFlag = false;
				}
			}

			else
			{
				if (iterator % 2 == 0)
					for (int i = 0; i < this->board.getNumOfGhosts(); i++) /*moving the ghosts*/
						smartGhost(this->board.getGhost(i), pacman, mode);
			}
		}
		else /*difficulity = BEST*/
		{
			if (iterator % 2 == 0)
				for (int i = 0; i < this->board.getNumOfGhosts(); i++) /*moving the ghosts*/
					smartGhost(this->board.getGhost(i), pacman, mode);
		}

		if (!fruit.getSpawnVal()) /*spawn and move fruit */
		{
			if (iterator % 200 == 0)
			{
				Position randomPos = (board.getEmptyPos())[rand() % (board.getEmptyPos()).size()];
				int randomX = randomPos.getX();
				int randomY = randomPos.getY();
				fruit.setObjectPosition(randomX, randomY);
				gotoxy(fruit.getObjectPositionY(), fruit.getObjectPositionX());
				cout << fruit.getIcon();
				fruit.setSpawnVal(true);
			}
		}

		else if (fruitIterator % 60 == 0)
		{
			gotoxy(fruit.getObjectPositionY(), fruit.getObjectPositionX());
			cout << board.getCharFromBoard(fruit.getObjectPositionX(), fruit.getObjectPositionY());
			fruit.~Fruit();
			fruitIterator = 1;
			fruit = Fruit();
		}

		else if (iterator % 4 == 0)
		{
			moveCreature(fruit, 69, mode);
			fruitIterator++;
		}

		if (_kbhit())
			handleButtonPress(direction, pacman, mode);

		if (this->board.getCharFromBoard(pacX, pacY) == breadCrumb) /*eating a breadcrumb and increasing the score*/
		{
			this->board.setCharToBoard(pacX, pacY, ' ');
			this->board.setNumOfCrumbs(this->board.getNumOfCrumbs() - 1);
			score = this->getScore() + 10;
			this->setScore(score);
		}


		printScoreAndLives(mode); /*printing the score and lives*/

		if (this->getLife() == 0) /*losing*/
			loseFlag = true;

		else if (this->board.getNumOfCrumbs() == 0) /*winning*/
			winFlag = true;


		if (deathFlag)
		{
			resultFile << "D " << iterator << endl;
			deathFlag = false;
		}

		iterator++;
	}

	if (loseFlag)
	{
		printWinLoseMessage(LOSE);
		return loseFlag;
	}

	else
	{
		resultFile << "F " << iterator << endl;
		return loseFlag;
	}
}

void Game::gotoxy(int x, int y)
{
	HANDLE hConsoleOutput;
	COORD dwCursorPosition;
	cout.flush();
	dwCursorPosition.X = x;
	dwCursorPosition.Y = y;
	hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hConsoleOutput, dwCursorPosition);
}

void Game::movePac(Pacman& pacman, Cord& pacX, Cord& pacY, char& direction, int mode)
/*this function is responssible of moving the pacman*/
{
	Cord oX = board.getbOrigin().getX(), oY = board.getbOrigin().getY();
	Cord eX = board.getbEnd().getX(), eY = board.getbEnd().getY();

	gotoxy(pacY, pacX);
	cout << " " << endl;

	switch (pacman.getDirection())
	{
	case 'W': case 'w':
		if (board.checkMove(pacX - 1, pacY, true))
			pacX--;
		break;

	case 'A': case 'a':
		if (board.checkMove(pacX, pacY - 1, true))
			pacY--;
		break;

	case 'D': case 'd':
		if (board.checkMove(pacX, pacY + 1, true))
			pacY++;
		break;

	case 'X': case 'x':
		if (board.checkMove(pacX + 1, pacY, true))
			pacX++;
		break;

	case 'S': case 's':
		break;
	}

	if (pacY == oY && (direction == 'a' || direction == 'A'))
	{
		pacY = eY + oY;
		pacman.setObjectPosition(pacX, pacY);
	}
	else if (pacY == (eY + oY) && (direction == 'd' || direction == 'D'))
	{
		pacY = oY;
		pacman.setObjectPosition(pacX, pacY);
	}
	else if (pacX == oX && (direction == 'w' || direction == 'W'))
	{
		pacX = eX + oX;
		pacman.setObjectPosition(pacX, pacY);
	}
	else if (pacX == (eX + oX) && (direction == 'x' || direction == 'X'))
	{
		pacX = oX;
		pacman.setObjectPosition(pacX, pacY);
	}
	else
		pacman.setObjectPosition(pacX, pacY);

	board.colorText(mode, 6);
	gotoxy(pacY, pacX);
	cout << pacman.getIcon() << endl;

	board.colorText(mode);
}

template <class Creature>
void Game::moveCreature(Creature& creature, int num, int mode)

/*this function are responssible of moving a creature according to his type*/
{
	Cord creatureX = creature.getObjectPositionX();
	Cord creatureY = creature.getObjectPositionY();
	char creatureDirection = creature.getDirection();
	char newDirection = 'W';
	int randomDir;

	gotoxy(creatureY, creatureX);
	cout << this->board.getCharFromBoard(creatureX, creatureY) << endl;

	switch (creatureDirection)
	{
	case 'W': case 'w':
		if (board.checkMove(creatureX - 1, creatureY, false))
			creatureX--;
		break;

	case 'A': case 'a':
		if (board.checkMove(creatureX, creatureY - 1, false))
			creatureY--;
		break;

	case 'D': case 'd':
		if (board.checkMove(creatureX, creatureY + 1, false))
			creatureY++;
		break;

	case 'X': case 'x':
		if (board.checkMove(creatureX + 1, creatureY, false))
			creatureX++;
		break;

	case 'S': case 's':
		break;
	}

	if (board.checkMove(creatureX, creatureY, false))
	{
		srand(time(NULL));

		randomDir = 0;

		while (randomDir == 0)
		{
			randomDir = (rand() * num) % 5;

			switch (randomDir)
			{
			case 1:
				newDirection = 'A';
				break;
			case 2:
				newDirection = 'D';
				break;
			case 3:
				newDirection = 'W';
				break;
			case 4:
				newDirection = 'X';
				break;
			}
		}

		creature.setDirection(newDirection);
	}

	creature.setObjectPosition(creatureX, creatureY);

	board.colorText(mode, creature.getColor());
	gotoxy(creatureY, creatureX);
	cout << creature.getIcon() << endl;
	board.colorText(mode);
}

void Game::smartGhost(Ghost& ghost, Pacman& pac, int mode)
/*this function uses BFS algorithem to find the shortest legal path to the pacman and moves according to the results of it*/
{
	Cord ghostX = ghost.getObjectPositionX();
	Cord ghostY = ghost.getObjectPositionY();

	int minInd = -1;

	chint up, down, right, left, min1, min2, res;
	up.len = -1;
	up.dir = 'w';
	down.len = -1;
	down.dir = 'x';
	right.len = -1;
	right.dir = 'd';
	left.len = -1;
	left.dir = 'a';

	if (board.checkMove(ghostX - 1, ghostY, false)) // up
		up.len = bestPathLen(ghostX - 1, ghostY, pac);

	if (board.checkMove(ghostX + 1, ghostY, false)) // down
		down.len = bestPathLen(ghostX + 1, ghostY, pac);

	if (board.checkMove(ghostX, ghostY - 1, false)) // left
		left.len = bestPathLen(ghostX, ghostY - 1, pac);

	if (board.checkMove(ghostX, ghostY + 1, false)) // right
		right.len = bestPathLen(ghostX, ghostY + 1, pac);

	if (up.len == -1 || down.len == -1)
		if (down.len != -1)
			min1 = down;
		else
			min1 = up;

	else if (up.len <= down.len)
		min1 = up;

	else
		min1 = down;

	if (left.len == -1 || right.len == -1)
		if (left.len != -1)
			min2 = left;
		else
			min2 = right;

	else if (left.len <= right.len)
		min2
		= left;
	else
		min2 = right;

	if (min1.len == -1 || min2.len == -1)
		if (min1.len != -1)
			res = min1;
		else
			res = min2;

	else if (min1.len <= min2.len)
		res = min1;

	else
		res = min2;

	if (res.len == -1)
		res.dir = ghost.getDirection();


	gotoxy(ghostY, ghostX);
	cout << board.getCharFromBoard(ghostX, ghostY);

	board.colorText(mode, ghost.getColor());

	switch (res.dir)
	{
	case 'w': case 'W': // up
		if (board.checkMove(ghostX - 1, ghostY, false))
		{
			ghost.setObjectPosition(ghostX - 1, ghostY);
			gotoxy(ghostY, ghostX - 1);
			cout << ghost.getIcon();
		}
		else
		{
			gotoxy(ghostY, ghostX);
			cout << ghost.getIcon();
		}
		break;

	case 'x': case 'X': // down
		if (board.checkMove(ghostX + 1, ghostY, false))
		{
			ghost.setObjectPosition(ghostX + 1, ghostY);
			gotoxy(ghostY, ghostX + 1);
			cout << ghost.getIcon();
		}
		else
		{
			gotoxy(ghostY, ghostX);
			cout << ghost.getIcon();
		}
		break;

	case 'a': case 'A':// left
		if (board.checkMove(ghostX, ghostY - 1, false))
		{
			ghost.setObjectPosition(ghostX, ghostY - 1);
			gotoxy(ghostY - 1, ghostX);
			cout << ghost.getIcon();
		}
		else
		{
			gotoxy(ghostY, ghostX);
			cout << ghost.getIcon();
		}
		break;

	case 'd': case 'D':// right
		if (board.checkMove(ghostX, ghostY + 1, false))
		{
			ghost.setObjectPosition(ghostX, ghostY + 1);
			gotoxy(ghostY + 1, ghostX);
			cout << ghost.getIcon();
		}
		else
		{
			gotoxy(ghostY, ghostX);
			cout << ghost.getIcon();
		}
		break;

	default:
		break;
	}

	board.colorText(mode);
}

int Game::bestPathLen(Cord ghostX, Cord ghostY, Pacman& pac)
{
	/* this function uses BFS algorithm to find the shortest path to Pacman, from given Cordinations */
	Position pacPos = Position(pac.getObjectPositionX(), pac.getObjectPositionY());
	int H = board.getbEnd().getX() - board.getbOrigin().getX();
	int W = board.getbEnd().getY() - board.getbOrigin().getY();
	vector<vector<bool>> visited(H, vector<bool>(W, false));

	for (int i = 0; i < H; i++) {
		for (int j = 0; j < W; j++)
		{
			if (board.getCharFromBoard(i, j) == '#')
				visited[i][j] = true;
			else
				visited[i][j] = false;
		}
	}


	queue<dPos> q;
	dPos curr;
	curr.pos = Position(ghostX, ghostY);
	curr.distance = 0;
	q.push(curr);
	visited[ghostX][ghostY] = true;

	while (!q.empty()) {
		dPos p = q.front();
		q.pop();

		Cord pX = p.pos.getX();
		Cord pY = p.pos.getY();

		// Destination found;
		if (pX == pacPos.getX() && pY == pacPos.getY())
			return p.distance;

		// moving up
		if (board.checkMove(pX - 1, pY, false) && visited[pX - 1][pY] == false)
		{
			curr.pos = Position(pX - 1, pY);
			curr.distance = p.distance + 1;
			q.push(curr);
			visited[pX - 1][pY] = true;
		}

		// moving down
		if (board.checkMove(pX + 1, pY, false) && visited[pX + 1][pY] == false)
		{
			curr.pos = Position(pX + 1, pY);
			curr.distance = p.distance + 1;
			q.push(curr);
			visited[pX + 1][pY] = true;
		}

		// moving left
		if (board.checkMove(pX, pY - 1, false) && visited[pX][pY - 1] == false)
		{
			curr.pos = Position(pX, pY - 1);
			curr.distance = p.distance + 1;
			q.push(curr);
			visited[pX][pY - 1] = true;
		}

		// moving right
		if (board.checkMove(pX, pY + 1, false) && visited[pX][pY + 1] == false)
		{
			curr.pos = Position(pX, pY + 1);
			curr.distance = p.distance + 1;
			q.push(curr);
			visited[pX][pY + 1] = true;
		}

	}

	return -1;
}

void Game::pausingLoop()
/*this function contains a loop for pausing the game situation*/
{
	bool pauseFlag = true;
	char key;

	while (pauseFlag)
	{
		if (_kbhit())
		{
			key = _getch();

			if (key == 0 || key == -32)
				key = _getch();

			else
				pauseFlag = false;
		}
	}
}

void Game::printScoreAndLives(int mode)
/*this function prints the score and the lives of the current game*/
{
	Cord x = board.getLifeScorePos().getX(), y = board.getLifeScorePos().getY();

	board.colorText(mode);
	gotoxy(y, x);
	cout << "SCORE: " << this->score;

	gotoxy(y, x + 1);
	cout << "LIVES: ";
	cout << "            ";

	board.colorText(mode, 4);
	gotoxy(y + 7, x + 1);
	for (int i = 0; i < this->life; i++)
		cout << "<3 ";
	board.colorText(mode);
}

void Game::printPausingMessage(int mode)
/*this function prints pausing message according to the user choice (colored\uncolored)*/
{
	board.colorText(mode, 4);
	gotoxy(board.getWidth() / 3, (board.getHeight() / 2) - 1);
	cout << "                        ";
	gotoxy(board.getWidth() / 3, board.getHeight() / 2);
	cout << "      GAME PAUSED!      ";
	gotoxy(board.getWidth() / 3, (board.getHeight() / 2) + 1);
	cout << " Press ESC to continue. ";
	gotoxy(board.getWidth() / 3, (board.getHeight() / 2) + 2);
	cout << "                        ";

	board.colorText(mode);
}

bool Game::isEaten(Pacman& pacman, Cord& pacX, Cord& pacY, int& fruitIterator)
/*this function checks if the pacman been eaten and updates the lives*/
{
	int i, j;
	int fruitX = board.getFruit().getObjectPositionX();
	int fruitY = board.getFruit().getObjectPositionY();
	for (i = 0; i < board.getNumOfGhosts(); i++)
	{

		if (pacman.getObjectPositionX() == board.getGhost(i).getObjectPositionX() && pacman.getObjectPositionY() == board.getGhost(i).getObjectPositionY())
		{
			Beep(600, 500);

			this->setLife(this->getLife() - 1);

			pacman.setPositionToSpawn();

			gotoxy(pacY, pacX);
			cout << ' ';

			for (j = 0; j < board.getNumOfGhosts(); j++)
			{
				gotoxy(board.getGhost(j).getObjectPositionY(), board.getGhost(j).getObjectPositionX());
				cout << ' ';
				board.getGhost(j).setPositionToSpawn();
			}

			pacX = pacman.getSpawnPos().getX();
			pacY = pacman.getSpawnPos().getY();

			pacman.setDirection('S');
			return true;
		}
		else if (board.getGhost(i).getObjectPositionX() == fruitX && board.getGhost(i).getObjectPositionY() == fruitY)
		{
			gotoxy(fruitY, fruitX);
			cout << board.getCharFromBoard(fruitX, fruitY);
			board.getFruit().~Fruit();
			fruitIterator = 1;
			board.getFruit() = Fruit();
		}
	}

	if (pacman.getObjectPositionX() == fruitX && pacman.getObjectPositionY() == fruitY)
	{
		gotoxy(fruitY, fruitX);
		cout << board.getCharFromBoard(fruitX, fruitY);
		setScore(getScore() + (board.getFruit().getIcon() - '0'));
		board.getFruit().~Fruit();
		fruitIterator = 1;
		board.getFruit() = Fruit();
	}

	return false;
}

vector<string> Game::loadFile(int& numOfFiles)
/*this function loads all the relevant screen files and sort them*/
{
	int i;
	vector <string> files;
	vector <string> screens;
	string dot = ".";

	for (const auto& entry : fs::directory_iterator(dot))
	{
		files.push_back(string(entry.path().string()));
	}

	for (i = 0; i < files.size(); i++)
	{
		size_t locate = files[i].find(".screen");
		if (locate != string::npos)
			screens.push_back(files[i]);
	}

	files.erase(files.begin(), files.end());
	numOfFiles = screens.size();

	if (numOfFiles == 0)
	{
		cout << "NO SCREEN FILES HAVE BEEN DETECTED IN THE WORKING DIRECTORY." << endl;
		cout << "MAKE SURE TO SET CORRECT WORKING DIRECTORY BEFORE RUNNING .EXE" << endl;
		Sleep(5000);
	}

	else
	{
		sort(screens.begin(), screens.end());
		return screens;
	}
}

void Game::printWinLoseMessage(int flag)
{
	system("cls");

	if (flag)
		cout << "YOU WON!!!" << endl;

	else
		cout << "YOU LOST!!!" << endl;


	cout << "PRESS ANY KEY TO CONTINUE." << endl;
	pausingLoop();
}

void Game::handleButtonPress(char& direction, Pacman& pacman, int mode)
{
	char key;

	key = _getch();

	if (key == 0 || key == -32)
		key = _getch();

	if (key == 'A' || key == 'a' || key == 'W' || key == 'w' || key == 'S' || key == 's' || key == 'D' || key == 'd' || key == 'X' || key == 'x')
	{
		direction = key;
		pacman.setDirection(direction);
	}

	if (key == ESC)
	{

		printPausingMessage(mode);

		bool pauseFlag = true;

		while (pauseFlag)
		{
			if (_kbhit())
			{
				key = _getch();

				if (key == 0 || key == -32)
					key = _getch();

				if (key == ESC)
					pauseFlag = false;
			}
		}
		system("cls");

		gotoxy(0, 0);
		this->board.drawBoard(mode);
	}
}

void Game::loadGameFromFile(string screenName, int arg)
/*this function supports the new features of ex3, reading a game from a step file, both regular or silent mode*/
{
	/*----------VARIABLES----------*/

	int iterator = 1;
	int i = 0;
	int fakeIterator = 0;

	char breadCrumb = 250;
	bool deathFlag = false;

	string line;
	string resLine;
	string stepsName;
	string resultName;

	ifstream stepsFile, resultFile;
	stepsName = screenName.erase(screenName.size() - 11, screenName.size()); stepsName.append(".steps");
	resultName = screenName; resultName.append(".result");
	stepsFile.open(stepsName, ios::in);
	resultFile.open(resultName, ios::in);

	Pacman& pacman = this->board.getPac();
	Fruit& fruit = board.getFruit();

	Cord pacX = this->board.getPac().getObjectPositionX();
	Cord pacY = this->board.getPac().getObjectPositionY();
	Cord fruitX;
	Cord fruitY;

	/*----------END OF VARIABLES----------*/

	/*----------CODE AND LOGICS----------*/

	getline(stepsFile, line); /*here we check if the number of ghosts in the file is equal to the number of ghosts in the board*/

	if ((line[0] - '0') != this->board.getNumOfGhosts())
	{
		cout << "NUMBER OF GHOSTS IN STEPS FILE IS DIFFERENT FROM NUMBER OF GHOSTS ON THE SCREEN." << endl;
		exit(1);
	}

	if (arg == LOAD)
		this->board.drawBoard(0); /*drawing the board*/

	while (getline(stepsFile, line)) /*game loop*/
	{
		pacman.setDirection(line[0]);
		movePac(pacman, pacX, pacY, line[0], 0);

		if (arg == LOAD)
			Sleep(150);

		deathFlag = isEaten(pacman, pacX, pacY, fakeIterator);

		for (i = 0; i < board.getNumOfGhosts(); i++) /*move ghosts*/
		{
			board.getGhost(i).setDirection(line[2 + i]);
			Cord ghostX = board.getGhost(i).getObjectPositionX();
			Cord ghostY = board.getGhost(i).getObjectPositionY();

			if (arg == LOAD)
			{
				gotoxy(ghostY, ghostX);
				cout << this->board.getCharFromBoard(ghostX, ghostY) << endl;
			}

			switch (line[2 + (i * 2)])
			{
			case 'W': case 'w':
				if (board.checkMove(ghostX - 1, ghostY, false))
					ghostX--;
				break;

			case 'A': case 'a':
				if (board.checkMove(ghostX, ghostY - 1, false))
					ghostY--;
				break;

			case 'D': case 'd':
				if (board.checkMove(ghostX, ghostY + 1, false))
					ghostY++;
				break;

			case 'X': case 'x':
				if (board.checkMove(ghostX + 1, ghostY, false))
					ghostX++;
				break;

			case 'S': case 's':
				break;
			case '*':
				break;
			}

			board.getGhost(i).setObjectPosition(ghostX, ghostY);

			if (arg == LOAD)
			{
				gotoxy(ghostY, ghostX);
				cout << board.getGhost(i).getIcon() << endl;
			}
		}

		int fruitInd = 2 * i + 2;
		if (line[fruitInd] != '*' && !board.getFruit().getSpawnVal()) /*fruit just spawned*/
		{
			char a = line[fruitInd + 2];
			int dig1 = 0, dig2 = 0;

			while (a != ',') /*reading a two digits number from the string*/
			{
				dig1++;
				a = line[fruitInd + 2 + dig1];
			}

			fruitX = strToInt(line.substr(fruitInd + 2, dig1));

			while (a != ' ')/*reading a two digits number from the string*/
			{
				dig2++;
				a = line[fruitInd + 2 + dig1 + dig2];
			}

			dig2--;
			fruitY = strToInt(line.substr(fruitInd + 2 + dig1 + 1, dig2));

			board.getFruit().setSpawnVal(true);
			board.getFruit().setDirection(line[fruitInd]);

			board.getFruit().setObjectPosition(fruitX, fruitY);
			board.getFruit().setIcon(line[fruitInd + 2 + dig1 + dig2 + 2]);

			if (arg == LOAD)
			{
				gotoxy(board.getFruit().getObjectPositionY(), board.getFruit().getObjectPositionX());
				cout << board.getFruit().getIcon();
			}
		}

		else if (line[fruitInd] != '*') /*move fruit*/
		{
			char a = line[fruitInd + 2];
			int dig1 = 0, dig2 = 0;

			while (a != ',')/*reading a two digits number from the string*/
			{
				dig1++;
				a = line[fruitInd + 2 + dig1];
			}

			fruitX = strToInt(line.substr(fruitInd + 2, dig1));

			while (a != ' ')/*reading a two digits number from the string*/
			{
				dig2++;
				a = line[fruitInd + 2 + dig1 + dig2];
			}

			dig2--;
			fruitY = strToInt(line.substr(fruitInd + 2 + dig1 + 1, dig2));

			if (arg == LOAD)
			{
				gotoxy(board.getFruit().getObjectPositionY(), board.getFruit().getObjectPositionX());
				cout << board.getCharFromBoard(board.getFruit().getObjectPositionX(), board.getFruit().getObjectPositionY());
			}

			board.getFruit().setObjectPosition(fruitX, fruitY);

			if (arg == LOAD)
			{
				gotoxy(board.getFruit().getObjectPositionY(), board.getFruit().getObjectPositionX());
				cout << board.getFruit().getIcon();
			}
		}

		else if (board.getFruit().getSpawnVal())
			board.getFruit().setSpawnVal(false);

		if (deathFlag) /*checking if the data is the same as in result file*/
		{
			getline(resultFile, resLine);

			if (resLine[0] != 'D')
			{
				system("cls");
				cout << "TEST FAILED. PACMAN DIED IN GAME BUT NOT IN STEPS." << endl;
				exit(0);
			}

			int deathTime = strToInt(resLine.substr(2, resLine.size() - 2));

			if (deathTime != iterator)
			{
				system("cls");
				cout << "TEST FAILED. PACMAN DIES AT THE WRONG TIME: " << iterator << " " << resLine << endl;
				exit(0);
			}

			else
				deathFlag = false;
		}

		if (this->board.getCharFromBoard(pacX, pacY) == breadCrumb) /*eating a breadcrumb and increasing the score*/
		{
			this->board.setCharToBoard(pacX, pacY, ' ');
			this->board.setNumOfCrumbs(this->board.getNumOfCrumbs() - 1);
			score = this->getScore() + 10;
			this->setScore(score);
		}

		if (arg == LOAD)
			printScoreAndLives(0);

		iterator++;
	}

	getline(resultFile, resLine);

	if (resLine[0] != 'F') /*checking if the data is the same as in result file*/
	{
		system("cls");
		cout << "TEST FAILED. SCREEN FINISHED, BUT NOT IN STEPS." << endl;
		exit(0);
	}

	int winTime = strToInt(resLine.substr(2, resLine.size() - 2));

	if (winTime != iterator)
	{
		system("cls");
		cout << "TEST FAILED. SCREEN FINISHED AT THE WRONG TIME: " << iterator << " " << resLine << endl;
		exit(0);
	}
	
	else
	{
		system("cls");
		cout << "TEST SUCCESSFUL FOR SCREEN: " << screenName << endl;
		Sleep(3000);
	}
	/*----------END CODE AND LOGICS----------*/
}

int Game::strToInt(string str)
/*this function converts a string number to int*/
{
	int i, res = 0, multiplier = 1;
	bool isNeg = false;

	for (i = str.size() - 1; i >= 0; i--)
	{
		if (str[i] == '-')
			isNeg = true;
		else if (str[i] >= '0' && str[i] <= '9')
		{
			res += (str[i] - '0') * multiplier;
			multiplier *= 10;
		}
		else
		{
			cout << "wrong input, int token illegal";
			exit(0);
		}
	}

	if (isNeg)
		res *= -1;

	return res;
}