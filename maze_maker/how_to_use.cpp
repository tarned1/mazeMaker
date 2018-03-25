#include<iostream>
#include "maze_maker.h"
#include<conio.h>
#include<fstream>
#define SIZE_X 25
#define SIZE_Y 50

using namespace std;

int main()
{
	maze_maker f;
	fstream file("feedback.txt", fstream::in | fstream::out | fstream::app);
	int x = SIZE_Y / 2, y = 0;
	char keyboard = '/', hero = '@', choice, name[25], comment[1001];
	bool win = false;
	do
	{
	start:
		x = SIZE_Y / 2;
		y = 0;
		do {
			f.NULL_board();
			f.maze_builder(0, SIZE_Y / 2, 0);
			//x == SIZE_X - 1 && y == SIZE_Y / 2
		} while (!f.checkxy(SIZE_Y / 2 - 1, SIZE_X - 1) && !f.checkxy(SIZE_Y / 2 + 1, SIZE_X - 1) && !f.checkxy(SIZE_Y / 2, SIZE_X - 2));
		f.print_board();
		f.~maze_maker();
		win = false;
		hero = _getch();
		f.gotoxy(0, SIZE_X + 1);
		cout << "press q to quit, * to restart the maze, p to begin the same maze." << endl;
		f.gotoxy(SIZE_Y / 2, 0);
		cout << hero;
		do {
			f.gotoxy(SIZE_Y, SIZE_X);
			keyboard = _getch();
			f.gotoxy(x, y);
			switch (keyboard)
			{
			case 'a': case 'A':
				if (x && f.checkxy(x - 1, y))
				{
					if (x == SIZE_Y / 2 && y == 0)
						cout << '*';
					else
						cout << ' ';
					x--;
				}
				break;

			case 's': case 'S':
				if (y + 1 != SIZE_X && f.checkxy(x, y + 1))
				{
					if (x == SIZE_Y / 2 && y == 0)
						cout << '*';
					else
						cout << ' ';
					y++;
				}
				break;
			case 'd': case 'D':
				if (x + 1 != SIZE_Y && f.checkxy(x + 1, y))
				{
					if (x == SIZE_Y / 2 && y == 0)
						cout << '*';
					else
						cout << ' ';
					x++;
				}
				break;
			case 'w': case 'W':
				if (y && f.checkxy(x, y - 1))
				{
					if (x == SIZE_Y / 2 && y == 0)
						cout << '*';
					else
						cout << ' ';
					y--;
				}
				break;
			case 'p': case'P':
				cout << ' ';
				f.gotoxy(SIZE_Y / 2, 0);
				x = SIZE_Y / 2;
				y = 0;
				break;
			case '*':
				goto start;
			case 'q': case 'Q':
				break;
			}
			f.gotoxy(x, y);
			cout << hero;
			if (x == SIZE_Y / 2 && y == SIZE_X - 1)
			{
				win = true;
				keyboard = 'q';
			}
		} while (keyboard != 'Q' && keyboard != 'q');
		f.gotoxy(0, SIZE_X);
		if (win)
			cout << "you are victorious!!!" << endl;
		else
			cout << "what a looser!!!" << endl;
		f.gotoxy(0, SIZE_X + 2);
		system("pause");
		system("cls");
		cout << "do you want to play again?[y/n]" << endl;

		choice = _getch();
		while (choice != 'y' && choice != 'n')
		{
			choice = _getch();
		}
	} while (choice == 'y');

	system("cls");

	cout << "                feedback:" << endl << endl;

	cout << "did you have fun?[y/n]" << endl;

	choice = _getch();

	while (choice != 'y' && choice != 'n')
	{
		choice = _getch();
	}

	cout << "enter your name: " << endl;

	cin >> name;

	cout << "enter your comment:" << endl;

	cin.getline(comment, 1000, '.');

	system("pause");

	if (strcmp(name, "eranagan123"))
		file << name << ": " << choice << endl << comment;
	else
	{
		system("cls");
		cout << "Hello admin!!!!" << endl;
		cout << "feedback:" << endl;
		while (!file.eof())
		{
			file.get(choice);
			if (!file.eof())
				cout << choice;
		}
		cout << endl;
		system("pause");
	}
	file.close();

	return 0;
}



