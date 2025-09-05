#include <iostream>
#include <conio.h>
#include 	<ctime>
#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif
using namespace std;
bool gameOver;
const int width = 40;
const int height = 20;
int x, y, fruitX, fruitY,score;
int tailX[100], tailY[100];
int nTail;
enum eDirection  {STOP = 0, UP,LEFT,DOWN,RIGHT};
eDirection dir;




void Setup()
{
	gameOver = false;
	dir = STOP;
	x = width / 2;
	y = height / 2;
	srand(time(0));
	fruitX = rand() % width;
	fruitY = rand() % height;
	score = 0;
}

void Draw()
{
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { 0,0 });
	//deflickers due to not constant printing
	CONSOLE_CURSOR_INFO info;

	info.dwSize = 100;

	info.bVisible = false;

	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &info);
	//removes console cursor when printing
	for (int i = 0; i < width + 2; i++)
		cout << "#";
	cout << endl;

	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			if (j == 0)
				cout << "#";
			if (i == y && j == x)
				cout << "O";
			else if (i == fruitY && j == fruitX)
				cout << "F";
			else
			{
				bool print = false;
				for (int k = 0; k < nTail; k++)
				{
					if (tailX[k] == j && tailY[k] == i)
					{
						cout << "o";
						print = true;
					}
				}
				if (!print)
					cout << " ";
			}


			if (j == width - 1)
				cout << "#";
		}
		cout << endl;
	}

	for (int i = 0; i < width + 2; i++)
		cout << "#";
	cout << endl;
	cout << "Score:" << score << endl;
}

	

//cout = character output
//the playfield is going crazy due to 
//being constantly drawn 
//even tho only the snake and fruit need to be
//idk how to fix this yet tho
//either string instead of cout or not constant iterations

void Input() 
{
	if (_kbhit())
	{
		switch (_getch())
		{
		case 'w':
			dir = UP;
			break;

		case 'a':
			dir = LEFT;
			break;

		case 's':
			dir = DOWN;
			break;

		case 'd':
			dir = RIGHT;
			break;

		case 'x':
			gameOver = true;
			break;
		}
	}

}
void Logic() 

{
	int prevX = tailX[0];
	int prevY = tailY[0];
	int prev2X, prev2Y;
	tailX[0] = x;
	tailY[0] = y;
	for (int i = 1; i < nTail; i++)
	{
		prev2X = tailX[i];
		prev2Y = tailY[i];
		tailX[i] = prevX;
		tailY[i] = prevY;
		prevX = prev2X;
		prevY = prev2Y;
	}
	//fruit killing u seems to have come from stop dir, instead now implemented sleep instead to slow down on my cpu.
	switch (dir)
	{

	case UP:
		y--;
		
		break;

	case LEFT:
		x--;
		
		break;

	case DOWN:
		y++;
		
		break;

	case RIGHT:
		x++;
		
		break;

	

	default:
	    break;
	}
	//if (x > width || x < 0 || y > height || y < 0)
		//gameOver = true;
	if (x >= width) x = 0; else if (x < 0) x = width - 1;
	if (y >= height) y = 0; else if (y < 0) x = height - 1;
	
	for (int i = 0; i < nTail; i++) 
		if (tailX[i] == x && tailY[i] == y)
			gameOver = true;
		
	
	if (x == fruitX && y == fruitY)
	{
		score += 10;
	
		
		fruitX = rand() % width;
		fruitY = rand() % height;
		//fruit are yet not truly random, always spawning in the same spot
		//done for today now tho, 11:44 03.09.25
		//started working around 10 prob
		nTail++;
	}
	
}
//snake yet too fast
	//s is dowen and a right but idk where it happens in ocde
	//all lines i can find say s should go left????
	//nnow it fully stopped recognizing input???
//it sees s on my keyboard as a and a as s???? WTF????
//turns out i accidentally swapped keycaps after cleaning my keyboard
int main()
{
	Setup();
	while (!gameOver) 
	{
	Draw();
	Input();
	Logic();
	Sleep(100);
	//sleep(120);
	
	}

	return 0;

}

