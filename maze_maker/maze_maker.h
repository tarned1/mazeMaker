#pragma once
#define SIZE_X 25
#define SIZE_Y 50
#define MAX SIZE_X + SIZE_Y
#include<iostream>
#include<windows.h>
#include<ctime>
using namespace std;
class maze_maker
{
public:
	maze_maker();

	struct member
	{
		bool print_view;
		int num_visit;
	};
	//check if a the cell have more than 1 neighbor
	bool check(int x, int y)
	{
		bool good = true;
		int count = 0;
		if (maze[x + 1][y].print_view && x != SIZE_X - 1)
			++count;
		if (maze[x - 1][y].print_view && x)
			++count;
		if (maze[x][y + 1].print_view && y)
			++count;
		if (maze[x][y - 1].print_view && y != SIZE_Y)
			++count;
		if (count > 1)
			good = false;
		return good;
	}
	//print's all the board
	void print_board()
	{
		gotoxy(0, 0);
		for (int i = 0; i < SIZE_X; ++i)
		{
			for (int j = 0; j < SIZE_Y; ++j)
			{
				if (maze[i][j].print_view)
					cout << ' ';
				else
					cout << '#';
			}
			cout << endl;
		}
		gotoxy(SIZE_Y / 2, 0);
		cout << '*';
		gotoxy(SIZE_Y / 2, SIZE_X - 1);
		cout << '&';
		gotoxy(SIZE_Y, SIZE_X);
	}
	//print 1 char in the console 
	void print_char(int x, int y)
	{
		gotoxy(y, x);
		if (maze[x][y].print_view)
			cout << ' ';
		else
			cout << '#';
	}
	//bilds a maze (recursive functoin)
	bool maze_builder(int x, int y, int count)
	{
		//the end
		if (x == SIZE_X - 1 && y == SIZE_Y / 2)
			return false;
		//a open space
		if (maze[x][y].print_view)
			return true;
		//to much to one darection
		if (count >= MAX)
		{
			return true;
		}
		//one then 1 neighbor
		if (!check(x, y))
			return true;
		//not the start
		if (x || y != SIZE_Y / 2)
		{
			maze[x][y].print_view = true;
			print_char(x, y);
		}
	label:
		choice = rand() % 100;
		if (!choice)
			return true;
		maze[x][y].num_visit++;
		choice = rand() % 4;
		switch (choice)
		{
		case 0:
			if (x)
			{
				if (maze[x][y].num_visit == 100)
					return true;
				else if (maze_builder(x - 1, y, count + 1))
					goto label;
			}
			else
				goto label;
			break;

		case 1:
			if (y)
			{
				if (maze[x][y].num_visit == 100)
					return true;
				else if (maze_builder(x, y - 1, count + 1))
					goto label;
			}
			else
				goto label;
			break;

		case 2:
			if (y != SIZE_Y - 1)
			{
				if (maze[x][y].num_visit == 100)
					return true;
				else if (maze_builder(x, y + 1, count + 1))
					goto label;
			}
			else
				goto label;
			break;

		case 3:
			if (x != SIZE_X - 1)
			{
				if (maze[x][y].num_visit == 100)
					return true;
				else if (maze_builder(x + 1, y, count + 1))
					goto label;
			}
			else
				goto label;
			break;
		}
	}

	~maze_maker();

private:
	member maze[SIZE_X][SIZE_Y] = { 0 };
	int choice;
	void gotoxy(int y, int x)
	{
		COORD coord;
		coord.X = y;
		coord.Y = x;
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
	}
};

maze_maker::maze_maker()
{
	srand((unsigned)time(NULL));
	print_board();
	maze_builder(0, SIZE_Y / 2, 0);
}

maze_maker::~maze_maker()
{
	gotoxy(0, SIZE_X);
	cout << "have fun" << endl;
}