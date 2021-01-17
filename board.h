#pragma once
#include "pieces.h"
#include "movement.h"
#include "game.h"
#include <iostream>
#include <string>
#include <vector>
#include <Windows.h>

using namespace std;

class Board
{
private:
	Piece** p;
public:
	Board(Piece** a)
	{
		p = a;
	}
	void drawHints(vector <vector <int>> h)
	{
		HANDLE color = GetStdHandle(STD_OUTPUT_HANDLE);
		char alpha = 'a';
		cout << "\t\t  1    2    3    4    5    6    7    8     \n";
		for (int i = 0; i < 8; i++)
		{
			cout << "\t\t=========================================\n\t\t";
			for (int j = 0; j < 8; j++)
			{
				cout << "| ";
				bool an = false;
				for (int k = 0; k < 32; k++)
				{
					int* s = p[k]->getSpot();
					if (i == s[0] && j == s[1] && !(p[k]->dead()))
					{

						if (p[k]->getColor() == 0)
						{
							SetConsoleTextAttribute(color, 1);
							cout << "B";
							cout << p[k]->getType();
							SetConsoleTextAttribute(color, 7);
						}
						else if (p[k]->getColor() == 1)
						{
							SetConsoleTextAttribute(color, 15);
							cout << "w";
							cout << (char)tolower(p[k]->getType());
							SetConsoleTextAttribute(color, 7);
						}

						an = true;
						break;
					}
				}
				bool star = false;
				for (unsigned int k = 0; k < h.size(); k++)
				{
					int p;
					char p1 = (char)tolower(h[k][0]);
					POSITION pchar = POSITION(p1);
					p = h[k][1];
					if (i == pchar && j == p)
					{
						star = true;
						SetConsoleTextAttribute(color, 10);
						if (!an) cout << " X";
						else cout << "X";
						SetConsoleTextAttribute(color, 7);
						break;
					}
				}
				if (!an && !star) cout << "  ";
				if(!star || (star && !an))cout << " ";
			}
			cout << "| " << char(alpha++) << endl;
		}
	}
	void draw()
	{
		HANDLE color = GetStdHandle(STD_OUTPUT_HANDLE);
		char alpha = 'a';
		cout << "\t\t  1    2    3    4    5    6    7    8     \n";
		for (int i = 0; i < 8; i++)
		{
			cout << "\t\t=========================================\n\t\t";
			for (int j = 0; j < 8; j++)
			{
				cout << "| ";
				bool an = false;
				for (int k = 0; k < 32; k++)
				{
					int* s = p[k]->getSpot();
					if (i == s[0] && j == s[1] && !(p[k]->dead()))
					{

						if (p[k]->getColor() == 0)
						{
							SetConsoleTextAttribute(color, 1);
							cout << "B";
							cout << p[k]->getType();
							SetConsoleTextAttribute(color, 7);
						}
						else if (p[k]->getColor() == 1)
						{
							SetConsoleTextAttribute(color, 15);
							cout << "w";
							cout << (char)tolower(p[k]->getType());
							SetConsoleTextAttribute(color, 7);
						}
						
						an = true;
						break;
					}
				}
				if (!an) cout << "  ";
				cout << " ";
			}
			cout << "| "<<char(alpha++)<<endl;
		}
	}
	void printLogo()
	{
		HANDLE color = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(color, 4);
		cout << "\t\t++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n";
		cout << "\t\t++	CCCCCCCCCC	HH\tHH	EEEEEEEEEE	EEEEEEEEEE	SSSSSSSSSS\t++\n";
		cout << "\t\t++	CC\t\tHH\tHH	EE\t\tEE	\tSS		++\n";
		cout << "\t\t++	CC\t\tHH\tHH	EE\t\tEE	\tSS		++\n";
		cout << "\t\t++	CC\t\tHHHHHHHHHH	EEEEEE    	EEEEEE\t\tSSSSSSSSSS\t++\n";
		cout << "\t\t++	CC\t\tHH\tHH	EE\t\tEE\t\t\tSS\t++\n";
		//cout << "\t++	CC\t\tHH\tHH	EE\t\tEE\t\t\tSS\t++\n";
		cout << "\t\t++	CCCCCCCCCC	HH\tHH	EEEEEEEEEE	EEEEEEEEEE\tSSSSSSSSSS\t++\n";
		cout << "\t\t++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n\n";
		SetConsoleTextAttribute(color, 7);
	}
	
	
};						 

