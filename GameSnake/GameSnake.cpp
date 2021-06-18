// C++
// Zmeya.cpp - ���� ��������� ���� "������", ��������� � �������, � ��� ������� - �������.

// ����������� ����������� ���������
#include <iostream>
#include <conio.h>
#include <windows.h>
#include <ctime>
#include <string>
#include <time.h>

// ����������� ������������ ���
using namespace std;

// ���������� ����������� ���������� ����������
bool GameOver;
const int WIDTH = 40;
const int HEIGHT = 20;
int x, y, fruitX, fruitY, score;
int tailX[100], tailY[100];
int nTail;
enum eDirection { STOP = 0, LEFT, RIGHT, UP, DOWN };
eDirection dir;
string LogicName = "";
int CountFPS = 0;
int FPS = 0;

void Setup() // ������� ��� ��������� ��������� ����
{
	srand(time(NULL));
	GameOver = false;
	dir = STOP;
	x = WIDTH / 2 - 1;
	y = HEIGHT / 2 - 1;
	nTail = 0;
	fruitX = rand() % WIDTH - 2;
	fruitY = rand() % HEIGHT - 2;
	score = 0;
}

void Draw() // ������� ��� ��������� ����� � ��������
{
	system("cls");

	for (int i = 0; i < WIDTH + 1; i++)
	{
		cout << "#";
	}

	cout << '\n';

	for (int i = 0; i < HEIGHT; i++)
	{
		for (int j = 0; j < WIDTH; j++)
		{
			if (j == 0 || j == WIDTH - 1)
			{
				cout << "#";
			}

			if (i == y && j == x)
			{
				cout << "0";
			}

			else if (i == fruitY && j == fruitX)
			{
				cout << "F";
			}

			else
			{
				bool print = false;
				for (int k = 0; k < nTail; k++)
				{
					if (tailX[k] == j && tailY[k] == i)
					{
						print = true;
						cout << "o";
					}
				}
				if (print == false)
					cout << " ";
			}
		}
		cout << '\n';
	}

	for (int i = 0; i < WIDTH + 1; i++)
	{
		cout << "#";
	}

	cout << '\n';
	cout << '\n' << "����: " << score << '\n';
	cout << '\n' << "���������: " << LogicName << '\n';
	cout << '\n' << "FPS: " << FPS << '\n';
	cout << '\n' << "������� X - ��� ������." << '\n';
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

		case 'd':
			dir = RIGHT;
			break;

		case 'w':
			dir = UP;
			break;

		case 's':
			dir = DOWN;
			break;

		case 'x':
			GameOver = true;
			break;
		}
	}
}

void LogicHard() // ������� ��� ������ ���� �� ��������� Hard
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

	switch (dir)
	{
	case LEFT:
		x--;
		break;
	case RIGHT:
		x++;
		break;
	case UP:
		y--;
		break;
	case DOWN:
		y++;
		break;
	}

	if (x > WIDTH - 2 || x < 0 || y > HEIGHT - 1 || y < 0)
	{
		GameOver = true;
	}

	for (int i = 0; i < nTail; i++)
	{
		if (tailX[i] == x && tailY[i] == y)
		{
			GameOver = true;
		}
	}

	if (x == fruitX && y == fruitY)
	{
		score += 10;
		fruitX = rand() % WIDTH - 2;
		fruitY = rand() % HEIGHT - 1;
		nTail++;
	}
}

void LogicEasy() // ������� ��� ������ ���� �� ��������� Easy
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

	switch (dir)
	{
	case LEFT:
		x--;
		break;
	case RIGHT:
		x++;
		break;
	case UP:
		y--;
		break;
	case DOWN:
		y++;
		break;
	}

	if (x >= WIDTH - 2)
	{
		x = 0;
	}

	else if (x <= 0)
	{
		x = WIDTH - 2;
	}

	if (y >= HEIGHT)
	{
		y = 0;
	}

	else if (y < 0)
	{
		y = HEIGHT;
	}

	for (int i = 0; i < nTail; i++)
	{
		if (tailX[i] == x && tailY[i] == y)
		{
			GameOver = true;
		}
	}

	if (x == fruitX && y == fruitY)
	{
		score += 10;
		fruitX = rand() % WIDTH - 2;
		fruitY = rand() % HEIGHT - 1;
		nTail++;
	}
}

int main() // ����� ����� � ���������
{
	setlocale(LC_ALL, "rus"); // ����������� ��� ������� ����

	time_t TimeFPS_1;
	time_t TimeFPS_2;

	while (true) // ������� ���� ���������
	{
		// ���������� ����������� ��������� ����������
		char select;
		int Time;

		system("cls"); // ������� �������

		// ������� ����
		for (int i = 0; i < WIDTH + 1; i++)
		{
			cout << "#";
		}

		cout << '\n';
		for (int i = 0; i < ((WIDTH + 1) / 2) - 5; i++)
		{
			cout << " ";
		}

		cout << "������� ����" << '\n';
		cout << "�������� ���������: " << '\n' << '\n' << "1 - ��� �������. " << '\n' << "2 - ��� �������. " << '\n' << '\n';
		cout << "��� �����(������� X - ��� ������): ";
		cin >> select; // ����� ��������� �������������

		switch (select) // ��������� ������ ������������
		{
		case '1':// ������ ���� �� ��������� Hard
			LogicName = "�������";
			Setup();
			
			TimeFPS_1 = time(NULL);
			while (!GameOver)
			{
				Draw();
				Input();
				LogicHard();
				TimeFPS_2 = time(NULL); 
				CountFPS++;
				if (TimeFPS_2 - TimeFPS_1 == 1) {
					FPS = CountFPS;
					CountFPS = 0;
					TimeFPS_1 = time(NULL);
				}
			}

			system("cls");
			Time = 3;
			while (Time > 0)
			{
				system("cls");
				for (int i = 0; i < WIDTH + 1; i++)
				{
					cout << "#";
				}
				cout << '\n';
				for (int i = 0; i < ((WIDTH + 1) / 2) - 5; i++)
				{
					cout << " ";
				}
				cout << "GAME OVER" << endl << endl << "����� � ������� ���� ����� " << Time << " ������!" << '\n';
				Sleep(1000);
				Time--;
			}
			continue;
			break;

		case '2': // ������ ���� �� ��������� Easy
			LogicName = "˸����";
			Setup();

			TimeFPS_1 = time(NULL);
			while (!GameOver)
			{
				Draw();
				Input();
				LogicEasy();
				TimeFPS_2 = time(NULL);
				CountFPS++;
				if (TimeFPS_2 - TimeFPS_1 == 1) {
					FPS = CountFPS;
					CountFPS = 0;
					TimeFPS_1 = time(NULL);
				}
			}

			system("cls");
			Time = 3;
			while (Time > 0)
			{
				system("cls");
				for (int i = 0; i < WIDTH + 1; i++)
				{
					cout << "#";
				}
				cout << '\n';
				for (int i = 0; i < ((WIDTH + 1) / 2) - 5; i++)
				{
					cout << " ";
				}
				cout << "GAME OVER" << endl << endl << "����� � ������� ���� ����� " << Time << " ������!" << '\n';
				Sleep(1000);
				Time--;
			}
			continue;
			break;

		case 'x':
			system("cls");
			for (int i = 0; i < WIDTH + 1; i++)
			{
				cout << "#";
			}
			cout << '\n';
			for (int i = 0; i < ((WIDTH + 1) / 2) - 5; i++)
			{
				cout << " ";
			}
			cout << "�������� �����!" << '\n' << '\n';

			system("pause");
			return 0;

			break;

		default:
			system("cls");
			Time = 3;
			while (Time > 0)
			{
				system("cls");
				for (int i = 0; i < WIDTH + 1; i++)
				{
					cout << "#";
				}
				cout << '\n';
				for (int i = 0; i < ((WIDTH + 1) / 2) - 10; i++)
				{
					cout << " ";
				}
				cout << "����������� ����� �����!\n����� � ������� ���� ����� " << Time << " ������!" << '\n';
				Sleep(1000);
				Time--;
			}
			continue;
			break;
		}
	}

	system("pause");
	return 0;
}
