#include <iostream>
#include <time.h>
#include <conio.h>
#include <windows.h>

using namespace std;

bool stop = false;
int width = 15;
int height = 15;
int positionX, positionY, fruitX, fruitY;
int score = 0;
int snakeX[225], snakeY[225];
int snakeSize;
enum eDirection { STOP = 0, LEFT, RIGHT, UP, DOWN };
eDirection dir;

void Setup();
void Draw();
void Input();
void Logic();

int main()
{
	srand(time(NULL));

	Setup();
	while (stop != true)
	{
		Draw();
		Input();
		Logic();
		Sleep(100);
	}
	return 0;
}

void Setup()
{
	stop = false;
	dir = STOP;
	positionX = rand() % width - 1;
	positionY = rand() % height - 1;
	fruitX = rand() % width - 3;
	fruitY = rand() % height - 3;
	score = 0;
}

void Draw()
{
	system("cls");

	for (int i = 0; i < width + 1; i++) cout << "#";
	cout << endl;

	for (int i = 0; i < width; i++)
	{
		for (int j = 0; j < height; j++)
		{
			if (j == 0 || j == width - 1) cout << "#";
			if (i == positionY && j == positionX) cout << "W";
			else if (i == fruitY && j == fruitX) cout << "@";
			else
			{
				bool output = false;
				for (int z = 0; z < snakeSize; z++)
				{
					if (snakeX[z] == j && snakeY[z] == i)
					{
						output = true;
						cout << "*";
					}
				}

				if (output == false) cout << " ";
			}
		}
		cout << endl;
	}

	for (int i = 0; i < width + 1; i++) cout << "#";

	cout << "\n\n\nscore: " << score << endl;
	cout << "x: " << positionX << " y: " << positionY;

}

void Input()
{
	if (_kbhit())
	{
		switch (_getch())
		{
		case 'a':
			dir = LEFT;
			break;

		case 'w':
			dir = UP;
			break;

		case 'd':
			dir = RIGHT;
			break;
		case 's':
			dir = DOWN;
			break;
		case 'q':
			stop = true;
			break;
		}
	}
}

void Logic()
{
	int prevX = snakeX[0];
	int prevY = snakeY[0];
	int prev2X, prev2Y;
	snakeX[0] = positionX;
	snakeY[0] = positionY;

	for (int i = 1; i < snakeSize; i++)
	{
		prev2X = snakeX[i];
		prev2Y = snakeY[i];
		snakeX[i] = prevX;
		snakeY[i] = prevY;
		prevX = prev2X;
		prevY = prev2Y;
	}
	switch (dir)
	{
	case UP:
		positionY--;
		break;
	case DOWN:
		positionY++;
		break;
	case RIGHT:
		positionX++;
		break;
	case LEFT:
		positionX--;
		break;
	}

	if (positionX >= width) positionX = 0;
	else if (positionX < 0) positionX = width - 1;

	if (positionY >= height) positionY = 0;
	else if (positionY < 0) positionY = height - 1;


	if (positionX > width - 1 || positionX < 0 || positionY > height - 1 || positionY < 0)
	{
		stop = true;
		system("cls");
		cout << "score: " << score << endl << endl << endl;
	}

	for (int i = 0; i < snakeSize; i++)
	{
		if (snakeX[i] == positionX && snakeY[i] == positionY)
		{
			stop = true;
			system("cls");
			cout << "score: " << score << endl << endl << endl;
		}
	}
	if (positionX == fruitX && positionY == fruitY)
	{
		score++;
		fruitX = rand() % width - 3;
		fruitY = rand() % height - 3;
		snakeSize++;

	}
}