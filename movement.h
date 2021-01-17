#pragma once
#include <iostream>
#include "game.h"
#include "pieces.h"
#include <string>
#include <vector>
#include "board.h"
#include <Windows.h>
using namespace std;

enum POSITION{a='a' , b='b' , c='c' , d ='d', e='e' , f='f' , g='g'};

class Move
{
private:
	Piece** p;
	color t;
public:
	Move(Piece** s , color& turn)
	{
		p = s;
		t = turn;			
	}
	int selectPiece()
	{
		char p1;
		char p2;
		int selected = -1;
		int pos[2];
		POSITION pchar;
		bool moveable = true;
		vector <vector <int>> moves;
		//Board b1(p);
		do
		{
			do
			{
				string turn = (t == WHITE) ? "WHITE" : "BLACK";
				cout << "it's " << turn << " turn\n";
				cout << "Enter position of piece to move: ";
				cin >> p1;
				cin >> p2;
				cin.ignore();
				p1 = (char)tolower(p1);
				pchar = (POSITION)(p1 - 'a');
				pos[0] = pchar;
				pos[1] = p2 - '0';

				pos[1] -= 1;
				for (int i = 0; i < 8; i++)
				{
					for (int j = 0; j < 8; j++)
					{
						for (int k = 0; k < 32; k++)
						{
							int* a = p[k]->getSpot();
							if (pos[0] == a[0] && pos[1] == a[1] && !(p[k]->dead()))
							{
								selected = k;
							}
						}
					}
				}
				if (selected < 0 || selected>31 || p[selected]->getColor() != t)
					cout << "Invalid piece selected!!!! TRY AGAIN.\n";
			} while (selected < 0 || selected>31 || p[selected]->getColor() != t);
			int send[2];
			send[1] = pos[1];
			send[0] = pos[0];
			moves = this->possibleMoves(selected, send);
			/*cout << "Possible Moves are { ";
			for (unsigned int i = 0; i < moves.size(); i++)
			{
				cout << char(moves[i][0] + 'a') << moves[i][1] + 1 << " ,";
			}
			cout << "}\n";*/
			if (moves.size() == 0)
			{
				cout << "THERE ARE NO MOVES SO SELECT ANYOTHER PIECE..\n";
				moveable = false;
			}
			else
				moveable = true;

		} while (!moveable);
		return selected;

	}

	void selectDestination(int selected)
	{
		HANDLE co = GetStdHandle(STD_OUTPUT_HANDLE);
		char p1, p2;
		POSITION pchar;
		bool isValid = false;
		int* pos = p[selected]->getSpot();
		vector <vector <int>> moves = this->possibleMoves(selected, pos);
		do
		{
			cout << "Select desitination: ";
			cin >> p1;
			cin >> p2;
			cin.ignore();
			p1 = (char)tolower(p1);
			pchar = (POSITION)(p1 - 'a');
			pos[0] = pchar;
			pos[1] = p2 - '0';
			pos[1]--;
			for (unsigned int i = 0; i < moves.size(); i++)
			{
				if (pos[0] == moves[i][0] && pos[1] == moves[i][1])
				{
					isValid = true;
					break;
				}
			}
			if (!isValid)
				cout << "NOT VALID MOVE . TRY AGAIN!!!\n";
			else
			{
				for (int i = 0; i < 32; i++)
				{
					if (i == selected)
						continue;
					int* spot = p[i]->getSpot();

					if (pos[0] == spot[0] && pos[1] == spot[1])
					{
						p[i]->captured();
						SetConsoleTextAttribute(co, 10);
						cout << "Opponent Piece Captured :)\n";
						SetConsoleTextAttribute(co, 7);
						Sleep(500);
					}
				}
				p[selected]->setSpot(pos);
				if (p[selected]->getType() == 'P')
					p[selected]->used();
				t = (t == 0) ? color(1) : color(0);
			}
		} while (!isValid);
	}
	vector <vector <int>> possibleMoves(int sel , int* position)
	{
		vector <vector <int>> moves;
		vector <int> m;
		int pos[2];
		pos[0]= position[0];
		pos[1] = position[1];
		if (p[sel]->getType() == 'P')
		{
			if (p[sel]->isStart())
			{
				if (p[sel]->getColor() == 1)
				{
					pos[0] += 1;
					m.push_back(pos[0]);
					m.push_back(pos[1]);
					moves.push_back(m);
					pos[0] += 1;
					m = {};
					m.push_back(pos[0]);
					m.push_back(pos[1]);
					moves.push_back(m);
					pos[0] = position[0];
					pos[0] += 1;
					pos[1] += 1;
					for (int i = 0; i < 32; i++)
					{
						if (i == sel)
							continue;
						int* s = p[i]->getSpot();
						if (pos[0] == s[0] && pos[1] == s[1] && p[sel]->getColor() != p[i]->getColor() && !p[i]->dead())
						{
							m = {};
							m.push_back(pos[0]);
							m.push_back(pos[1]);
							moves.push_back(m);
							break;
						}
					}
					pos[0] = position[0];
					pos[1] = position[1];
					pos[0] += 1;
					pos[1] -= 1;
					for (int i = 0; i < 32; i++)
					{
						if (i == sel)
							continue;
						int* s = p[i]->getSpot();
						if (pos[0] == s[0] && pos[1] == s[1] && p[sel]->getColor() != p[i]->getColor() && !p[i]->dead())
						{
							m = {};
							m.push_back(pos[0]);
							m.push_back(pos[1]);
							moves.push_back(m);
							break;
						}
					}
				}
				else
				{
					pos[0] -= 1;
					m.push_back(pos[0]);
					m.push_back(pos[1]);
					moves.push_back(m);
					pos[0] -= 1;
					m = {};
					m.push_back(pos[0]);
					m.push_back(pos[1]);
					moves.push_back(m);
					pos[0] = position[0];
					pos[0] -= 1;
					pos[1] -= 1;
					for (int i = 0; i < 32; i++)
					{
						if (i == sel)
							continue;
						int* s = p[i]->getSpot();
						if (pos[0] == s[0] && pos[1] == s[1] && p[sel]->getColor() != p[i]->getColor() && !p[i]->dead())
						{
							m = {};
							m.push_back(pos[0]);
							m.push_back(pos[1]);
							moves.push_back(m);
							break;
						}
					}
					pos[0] = position[0];
					pos[1] = position[1];
					pos[0] -= 1;
					pos[1] += 1;
					for (int i = 0; i < 32; i++)
					{
						if (i == sel)
							continue;
						int* s = p[i]->getSpot();
						if (pos[0] == s[0] && pos[1] == s[1] && p[sel]->getColor() != p[i]->getColor() && !p[i]->dead())
						{
							m = {};
							m.push_back(pos[0]);
							m.push_back(pos[1]);
							moves.push_back(m);
							break;
						}
					}
				}
			}
			else
			{
				if(p[sel]->getColor()==1)
				{
					pos[0] += 1;
					m.push_back(pos[0]);
					m.push_back(pos[1]);
					moves.push_back(m);
					pos[0] = position[0];
					pos[0] += 1;
					pos[1] += 1;
					for (int i = 0; i < 32; i++)
					{
						if (i == sel)
							continue;
						int* s = p[i]->getSpot();
						if (pos[0] == s[0] && pos[1] == s[1] && p[sel]->getColor() != p[i]->getColor() && !p[i]->dead())
						{
							m = {};
							m.push_back(pos[0]);
							m.push_back(pos[1]);
							moves.push_back(m);
							break;
						}
					}
					pos[0] = position[0];
					pos[1] = position[1];
					pos[0] += 1;
					pos[1] -= 1;
					for (int i = 0; i < 32; i++)
					{
						if (i == sel)
							continue;
						int* s = p[i]->getSpot();
						if (pos[0] == s[0] && pos[1] == s[1] && p[sel]->getColor() != p[i]->getColor() && !p[i]->dead())
						{
							m = {};
							m.push_back(pos[0]);
							m.push_back(pos[1]);
							moves.push_back(m);
							break;
						}
					}
				}
				else
				{
					pos[0] -= 1;
					m.push_back(pos[0]);
					m.push_back(pos[1]);
					moves.push_back(m);
					pos[0] = position[0];
					pos[0] -= 1;
					pos[1] -= 1;
					for (int i = 0; i < 32; i++)
					{
						if (i == sel)
							continue;
						int* s = p[i]->getSpot();
						if (pos[0] == s[0] && pos[1] == s[1] && p[sel]->getColor() != p[i]->getColor() && !p[i]->dead())
						{
							m = {};
							m.push_back(pos[0]);
							m.push_back(pos[1]);
							moves.push_back(m);
							break;
						}
					}
					pos[0] = position[0];
					pos[1] = position[1];
					pos[0] -= 1;
					pos[1] += 1;
					for (int i = 0; i < 32; i++)
					{
						if (i == sel)
							continue;
						int* s = p[i]->getSpot();
						if (pos[0] == s[0] && pos[1] == s[1] && p[sel]->getColor() != p[i]->getColor() && !p[i]->dead())
						{
							m = {};
							m.push_back(pos[0]);
							m.push_back(pos[1]);
							moves.push_back(m);
							break;
						}
					}
				}
			}
		}
		else if (p[sel]->getType() == 'R')
		{
			bool stp = false;
			while (pos[1] > 0 && !stp)
			{
				pos[1] -= 1;
				for (int i = 0; i < 32; i++)
				{
					if (i == sel)
						continue;
					int* spot = p[i]->getSpot();
					int col = p[i]->getColor();
					if (spot[0] == pos[0] && spot[1] == pos[1] ) 
					{
						if(col==p[sel]->getColor())
							stp = true;
						else
						{
							m = {};
							m.push_back(pos[0]);
							m.push_back(pos[1]);
							moves.push_back(m);
							stp = true;
						}
						break;
					}
				}
				if (!stp && pos[1]>=0)
				{
					m = {};
					m.push_back(pos[0]);
					m.push_back(pos[1]);
					moves.push_back(m);
				}
			}
			pos[0] = position[0];
			pos[1] = position[1];
			stp = false;
			while (pos[1] < 8 && !stp)
			{
				pos[1] += 1;
				for (int i = 0; i < 32; i++)
				{
					if (i == sel)
						continue;
					int* spot = p[i]->getSpot();
					int col = p[i]->getColor();
					if (spot[0] == pos[0] && spot[1] == pos[1])
					{
						if (col == p[sel]->getColor())
							stp = true;
						else
						{
							m = {};
							m.push_back(pos[0]);
							m.push_back(pos[1]);
							moves.push_back(m);
							stp = true;
						}
						break;
					}
				}
				if (!stp && pos[1]<8)
				{
					m = {};
					m.push_back(pos[0]);
					m.push_back(pos[1]);
					moves.push_back(m);
				}
			}
			pos[0] = position[0];
			pos[1] = position[1];
			stp = false;
			while (pos[0] < 8 && !stp)
			{
				pos[0] += 1;
				for (int i = 0; i < 32; i++)
				{
					if (i == sel)
						continue;
					int* spot = p[i]->getSpot();
					int col = p[i]->getColor();
					if (spot[0] == pos[0] && spot[1] == pos[1])
					{
						if (col == p[sel]->getColor())
							stp = true;
						else
						{
							m = {};
							m.push_back(pos[0]);
							m.push_back(pos[1]);
							moves.push_back(m);
							stp = true;
						}
						break;
					}
				}
				if (!stp && pos[0]<8)
				{
					m = {};
					m.push_back(pos[0]);
					m.push_back(pos[1]);
					moves.push_back(m);
				}
			}
			pos[0] = position[0];
			pos[1] = position[1];
			stp = false;
			while (pos[0] > 0 && !stp)
			{
				pos[0] -= 1;
				for (int i = 0; i < 32; i++)
				{
					if (i == sel)
						continue;
					int* spot = p[i]->getSpot();
					int col = p[i]->getColor();
					if (spot[0] == pos[0] && spot[1] == pos[1])
					{
						if (col == p[sel]->getColor())
							stp = true;
						else
						{
							m = {};
							m.push_back(pos[0]);
							m.push_back(pos[1]);
							moves.push_back(m);
							stp = true;
						}
						break;
					}
				}
				if (!stp && pos[0]>=0)
				{
					m = {};
					m.push_back(pos[0]);
					m.push_back(pos[1]);
					moves.push_back(m);
				}
			}

		}
		else if (p[sel]->getType() == 'Q')
		{
			bool stp = false;
			while (pos[0] > 0 && pos[1] > 0 && !stp)
			{
				pos[0] -= 1;
				pos[1] -= 1;
				for (int i = 0; i < 32; i++)
				{
					if (i == sel)
						continue;
					int* spot = p[i]->getSpot();
					int col = p[i]->getColor();
					if (spot[0] == pos[0] && spot[1] == pos[1])
					{
						if (col == p[sel]->getColor())
							stp = true;
						else
						{
							m = {};
							m.push_back(pos[0]);
							m.push_back(pos[1]);
							moves.push_back(m);
							stp = true;
						}
						break;
					}
				}
				if (!stp)
				{
					m = {};
					m.push_back(pos[0]);
					m.push_back(pos[1]);
					moves.push_back(m);
				}
			}
			pos[0] = position[0];
			pos[1] = position[1];
			stp = false;
			while (pos[0] < 8 && pos[1] < 8 && !stp)
		{
			pos[0] += 1;
			pos[1] += 1;
			for (int i = 0; i < 32; i++)
			{
				if (i == sel)
					continue;
				int* spot = p[i]->getSpot();
				int col = p[i]->getColor();
				if (spot[0] == pos[0] && spot[1] == pos[1])
				{
					if (col == p[sel]->getColor())
						stp = true;
					else
					{
						m = {};
						m.push_back(pos[0]);
						m.push_back(pos[1]);
						moves.push_back(m);
						stp = true;
					}
					break;
				}
			}
			if (!stp && pos[0] < 8 && pos[1] < 8)
			{
				m = {};
				m.push_back(pos[0]);
				m.push_back(pos[1]);
				moves.push_back(m);
			}
		}
			pos[0] = position[0];
			pos[1] = position[1];
			stp = false;
			while (pos[1] > 0 && pos[0] < 8 && !stp)
		{
			pos[1] -= 1;
			pos[0] += 1;
			for (int i = 0; i < 32; i++)
			{
				if (i == sel)
					continue;
				int* spot = p[i]->getSpot();
				int col = p[i]->getColor();
				if (spot[0] == pos[0] && spot[1] == pos[1])
				{
					if (col == p[sel]->getColor())
						stp = true;
					else
					{
						m = {};
						m.push_back(pos[0]);
						m.push_back(pos[1]);
						moves.push_back(m);
						stp = true;
					}
					break;
				}
			}
			if (!stp && pos[0] < 8)
			{
				m = {};
				m.push_back(pos[0]);
				m.push_back(pos[1]);
				moves.push_back(m);
			}
		}
			pos[0] = position[0];
			pos[1] = position[1];
			stp = false;
			while (pos[0] > 0 && pos[1] < 8 && !stp)
			{
				pos[0] -= 1;
				pos[1] += 1;
				for (int i = 0; i < 32; i++)
				{
					if (i == sel)
						continue;
					int* spot = p[i]->getSpot();
					int col = p[i]->getColor();
					if (spot[0] == pos[0] && spot[1] == pos[1])
					{
						if (col == p[sel]->getColor())
							stp = true;
						else
						{
							m = {};
							m.push_back(pos[0]);
							m.push_back(pos[1]);
							moves.push_back(m);
							stp = true;
						}
						break;
					}
				}
				if (!stp && pos[1])
				{
					m = {};
					m.push_back(pos[0]);
					m.push_back(pos[1]);
					moves.push_back(m);
				}
			}
			pos[0] = position[0];
			pos[1] = position[1];
			stp = false;
			while (pos[1] > 0 && !stp)
			{
				pos[1] -= 1;
				for (int i = 0; i < 32; i++)
				{
					if (i == sel)
						continue;
					int* spot = p[i]->getSpot();
					int col = p[i]->getColor();
					if (spot[0] == pos[0] && spot[1] == pos[1])
					{
						if (col == p[sel]->getColor())
							stp = true;
						else
						{
							m = {};
							m.push_back(pos[0]);
							m.push_back(pos[1]);
							moves.push_back(m);
							stp = true;
						}
						break;
					}
				}
				if (!stp && pos[1] >= 0)
				{
					m = {};
					m.push_back(pos[0]);
					m.push_back(pos[1]);
					moves.push_back(m);
				}
			}
			pos[0] = position[0];
			pos[1] = position[1];
			stp = false;
			while (pos[1] < 8 && !stp)
			{
				pos[1] += 1;
				for (int i = 0; i < 32; i++)
				{
					if (i == sel)
						continue;
					int* spot = p[i]->getSpot();
					int col = p[i]->getColor();
					if (spot[0] == pos[0] && spot[1] == pos[1])
					{
						if (col == p[sel]->getColor())
							stp = true;
						else
						{
							m = {};
							m.push_back(pos[0]);
							m.push_back(pos[1]);
							moves.push_back(m);
							stp = true;
						}
						break;
					}
				}
				if (!stp && pos[1] < 8)
				{
					m = {};
					m.push_back(pos[0]);
					m.push_back(pos[1]);
					moves.push_back(m);
				}
			}
			pos[0] = position[0];
			pos[1] = position[1];
			stp = false;
			while (pos[0] < 8 && !stp)
			{
				pos[0] += 1;
				for (int i = 0; i < 32; i++)
				{
					if (i == sel)
						continue;
					int* spot = p[i]->getSpot();
					int col = p[i]->getColor();
					if (spot[0] == pos[0] && spot[1] == pos[1])
					{
						if (col == p[sel]->getColor())
							stp = true;
						else
						{
							m = {};
							m.push_back(pos[0]);
							m.push_back(pos[1]);
							moves.push_back(m);
							stp = true;
						}
						break;
					}
				}
				if (!stp && pos[0] < 8)
				{
					m = {};
					m.push_back(pos[0]);
					m.push_back(pos[1]);
					moves.push_back(m);
				}
			}
			pos[0] = position[0];
			pos[1] = position[1];
			stp = false;
			while (pos[0] > 0 && !stp)
			{
				pos[0] -= 1;
				for (int i = 0; i < 32; i++)
				{
					if (i == sel)
						continue;
					int* spot = p[i]->getSpot();
					int col = p[i]->getColor();
					if (spot[0] == pos[0] && spot[1] == pos[1])
					{
						if (col == p[sel]->getColor())
							stp = true;
						else
						{
							m = {};
							m.push_back(pos[0]);
							m.push_back(pos[1]);
							moves.push_back(m);
							stp = true;
						}
						break;
					}
				}
				if (!stp && pos[0] >= 0)
				{
					m = {};
					m.push_back(pos[0]);
					m.push_back(pos[1]);
					moves.push_back(m);
				}
			}

		}
		else if (p[sel]->getType() == 'N')
		{
			bool valid = true;
			pos[0] -= 2;
			pos[1] -= 1;
			if (pos[0] >=0 && pos[1]>=0)
			{
				for (int i = 0; i < 32; i++)
				{
					if (i == sel)
						continue;
					int* spot = p[i]->getSpot();
					int col = p[i]->getColor();
					if (spot[0] == pos[0] && spot[1] == pos[1])
					{
						if (col == p[sel]->getColor())
						{
							valid = false;
							break;
						}
					}
				}
				if (valid)
				{
					m = {};
					m.push_back(pos[0]);
					m.push_back(pos[1]);
					moves.push_back(m);
				}
			}
			valid = true;
			pos[0] = position[0];
			pos[1] = position[1];
			pos[0] -= 1;
			pos[1] -= 2;
			if (pos[0] >= 0 && pos[1] >= 0)
			{
				for (int i = 0; i < 32; i++)
				{
					if (i == sel)
						continue;
					int* spot = p[i]->getSpot();
					int col = p[i]->getColor();
					if (spot[0] == pos[0] && spot[1] == pos[1])
					{
						if (col == p[sel]->getColor())
						{
							valid = false;
							break;
						}
					}
				}
				if (valid)
				{
					m = {};
					m.push_back(pos[0]);
					m.push_back(pos[1]);
					moves.push_back(m);
				}
			}
			valid = true;
			pos[0] = position[0];
			pos[1] = position[1];
			pos[0] -= 2;
			pos[1] += 1;
			if (pos[0] >= 0 && pos[1] < 8)
			{
				for (int i = 0; i < 32; i++)
				{
					if (i == sel)
						continue;
					int* spot = p[i]->getSpot();
					int col = p[i]->getColor();
					if (spot[0] == pos[0] && spot[1] == pos[1])
					{
						if (col == p[sel]->getColor())
						{
							valid = false;
							break;
						}
					}
				}
				if (valid)
				{
					m = {};
					m.push_back(pos[0]);
					m.push_back(pos[1]);
					moves.push_back(m);
				}
			}
			valid = true;
			pos[0] = position[0];
			pos[1] = position[1];
			pos[0] -= 1;
			pos[1] += 2;
			if (pos[0] >= 0 && pos[1] < 8)
			{
				for (int i = 0; i < 32; i++)
				{
					if (i == sel)
						continue;
					int* spot = p[i]->getSpot();
					int col = p[i]->getColor();
					if (spot[0] == pos[0] && spot[1] == pos[1])
					{
						if (col == p[sel]->getColor())
						{
							valid = false;
							break;
						}
					}
				}
				if (valid)
				{
					m = {};
					m.push_back(pos[0]);
					m.push_back(pos[1]);
					moves.push_back(m);
				}
			}
			valid = true;
			pos[0] = position[0];
			pos[1] = position[1];
			pos[0] += 1;
			pos[1] -= 2;
			if (pos[0] < 8 && pos[1] >= 0)
			{
				for (int i = 0; i < 32; i++)
				{
					if (i == sel)
						continue;
					int* spot = p[i]->getSpot();
					int col = p[i]->getColor();
					if (spot[0] == pos[0] && spot[1] == pos[1])
					{
						if (col == p[sel]->getColor())
						{
							valid = false;
							break;
						}
					}
				}
				if (valid)
				{
					m = {};
					m.push_back(pos[0]);
					m.push_back(pos[1]);
					moves.push_back(m);
				}
			}
			valid = true;
			pos[0] = position[0];
			pos[1] = position[1];
			pos[0] += 2;
			pos[1] -= 1;
			if (pos[0] < 8 && pos[1] >= 0)
			{
				for (int i = 0; i < 32; i++)
				{
					if (i == sel)
						continue;
					int* spot = p[i]->getSpot();
					int col = p[i]->getColor();
					if (spot[0] == pos[0] && spot[1] == pos[1])
					{
						if (col == p[sel]->getColor())
						{
							valid = false;
							break;
						}
					}
				}
				if (valid)
				{
					m = {};
					m.push_back(pos[0]);
					m.push_back(pos[1]);
					moves.push_back(m);
				}
			}
			valid = true;
			pos[0] = position[0];
			pos[1] = position[1];
			pos[0] += 1;
			pos[1] += 2;
			if (pos[0] < 8 && pos[1] < 8)
			{
				for (int i = 0; i < 32; i++)
				{
					if (i == sel)
						continue;
					int* spot = p[i]->getSpot();
					int col = p[i]->getColor();
					if (spot[0] == pos[0] && spot[1] == pos[1])
					{
						if (col == p[sel]->getColor())
						{
							valid = false;
							break;
						}
					}
				}
				if (valid)
				{
					m = {};
					m.push_back(pos[0]);
					m.push_back(pos[1]);
					moves.push_back(m);
				}
			}
			valid = true;
			pos[0] = position[0];
			pos[1] = position[1];
			pos[0] += 2;
			pos[1] += 1;
			if (pos[0] < 8 && pos[1] < 8)
			{
				for (int i = 0; i < 32; i++)
				{
					if (i == sel)
						continue;
					int* spot = p[i]->getSpot();
					int col = p[i]->getColor();
					if (spot[0] == pos[0] && spot[1] == pos[1])
					{
						if (col == p[sel]->getColor())
						{
							valid = false;
							break;
						}
					}
				}
				if (valid)
				{
					m = {};
					m.push_back(pos[0]);
					m.push_back(pos[1]);
					moves.push_back(m);
				}
			}
		}
		else if (p[sel]->getType() == 'B')
		{
			bool stp = false;
			while(pos[0]>0 && pos[1]>0 && !stp)
			{ 
				pos[0] -= 1;
				pos[1] -= 1;
				for (int i = 0; i < 32; i++)
				{
					if (i == sel)
						continue;
					int* spot = p[i]->getSpot();
					int col = p[i]->getColor();
					if (spot[0] == pos[0] && spot[1] == pos[1])
					{
						if (col == p[sel]->getColor())
							stp = true;
						else
						{
							m = {};
							m.push_back(pos[0]);
							m.push_back(pos[1]);
							moves.push_back(m);
							stp = true;
						}
						break;
					}
				}
				if (!stp)
				{
					m = {};
					m.push_back(pos[0]);
					m.push_back(pos[1]);
					moves.push_back(m);
				}
			}
			pos[0] = position[0];
			pos[1] = position[1];
			stp = false;
			while(pos[0]<8 && pos[1]<8 && !stp)
			{
				pos[0] += 1;
				pos[1] += 1;
				for (int i = 0; i < 32; i++)
				{
					if (i == sel)
						continue;
					int* spot = p[i]->getSpot();
					int col = p[i]->getColor();
					if (spot[0] == pos[0] && spot[1] == pos[1])
					{
						if (col == p[sel]->getColor())
							stp = true;
						else
						{
							m = {};
							m.push_back(pos[0]);
							m.push_back(pos[1]);
							moves.push_back(m);
							stp = true;
						}
						break;
					}
				}
				if (!stp && pos[0]<8 && pos[1]<8)
				{
					m = {};
					m.push_back(pos[0]);
					m.push_back(pos[1]);
					moves.push_back(m);
				}
			}
			pos[0] = position[0];
			pos[1] = position[1];
			stp = false;
			while(pos[1]>0 && pos[0]<8 && !stp)
			{
				pos[1] -= 1;
				pos[0] += 1;
				for (int i = 0; i < 32; i++)
				{
					if (i == sel)
						continue;
					int* spot = p[i]->getSpot();
					int col = p[i]->getColor();
					if (spot[0] == pos[0] && spot[1] == pos[1])
					{
						if (col == p[sel]->getColor())
							stp = true;
						else
						{
							m = {};
							m.push_back(pos[0]);
							m.push_back(pos[1]);
							moves.push_back(m);
							stp = true;
						}
						break;
					}
				}
				if (!stp && pos[0]<8)
				{
					m = {};
					m.push_back(pos[0]);
					m.push_back(pos[1]);
					moves.push_back(m);
				}
			}
			pos[0] = position[0];
			pos[1] = position[1];
			stp = false;
			while(pos[0]>0 && pos[1]<8 && !stp)
			{ 
				pos[0] -= 1;
				pos[1] += 1;
				for (int i = 0; i < 32; i++)
				{
					if (i == sel)
						continue;
					int* spot = p[i]->getSpot();
					int col = p[i]->getColor();
					if (spot[0] == pos[0] && spot[1] == pos[1])
					{
						if (col == p[sel]->getColor())
							stp = true;
						else
						{
							m = {};
							m.push_back(pos[0]);
							m.push_back(pos[1]);
							moves.push_back(m);
							stp = true;
						}
						break;
					}
				}
				if (!stp && pos[1])
				{
					m = {};
					m.push_back(pos[0]);
					m.push_back(pos[1]);
					moves.push_back(m);
				}
			}

		}
		else if (p[sel]->getType() == 'K')
		{
			bool valid = true;
			if (pos[0] < 7)
			{
				pos[0] += 1;
				for (int i = 0; i < 32; i++)
				{
					if (i == sel)
						continue;
					int* spot = p[i]->getSpot();
					int col = p[i]->getColor();
					if (spot[0] == pos[0] && spot[1] == pos[1])
					{
						if (col == p[sel]->getColor())
						{
							valid = false;
							break;
						}
					}
				}
				if (valid)
				{
					m = {};
					m.push_back(pos[0]);
					m.push_back(pos[1]);
					moves.push_back(m);
				}
			}
			pos[0] = position[0];
			pos[1] = position[1];
			if (pos[0] > 0)
			{
				pos[0] -= 1;
				valid = true;
				for (int i = 0; i < 32; i++)
				{
					if (i == sel)
						continue;
					int* spot = p[i]->getSpot();
					int col = p[i]->getColor();
					if (spot[0] == pos[0] && spot[1] == pos[1])
					{
						if (col == p[sel]->getColor())
						{
							valid = false;
							break;
						}
					}
				}
				if (valid)
				{
					m = {};
					m.push_back(pos[0]);
					m.push_back(pos[1]);
					moves.push_back(m);
				}
			}
			pos[0] = position[0];
			pos[1] = position[1];
			if (pos[1] < 7)
			{
				pos[1] += 1;
				valid = true;
				for (int i = 0; i < 32; i++)
				{
					if (i == sel)
						continue;
					int* spot = p[i]->getSpot();
					int col = p[i]->getColor();
					if (spot[0] == pos[0] && spot[1] == pos[1])
					{
						if (col == p[sel]->getColor())
						{
							valid = false;
							break;
						}
					}
				}
				if (valid)
				{
					m = {};
					m.push_back(pos[0]);
					m.push_back(pos[1]);
					moves.push_back(m);
				}
			}
			pos[0] = position[0];
			pos[1] = position[1];
			if (pos[1] > 0)
			{
				pos[1] -= 1;
				valid = true;
				for (int i = 0; i < 32; i++)
				{
					if (i == sel)
						continue;
					int* spot = p[i]->getSpot();
					int col = p[i]->getColor();
					if (spot[0] == pos[0] && spot[1] == pos[1])
					{
						if (col == p[sel]->getColor())
						{
							valid = false;
							break;
						}
					}
				}
				if (valid)
				{
					m = {};
					m.push_back(pos[0]);
					m.push_back(pos[1]);
					moves.push_back(m);
				}
			}
			pos[0] = position[0];
			pos[1] = position[1];
			if (pos[0] < 7 && pos[1]>0)
			{
				pos[0] += 1;
				pos[1] -= 1;
				valid = true;
				for (int i = 0; i < 32; i++)
				{
					if (i == sel)
						continue;
					int* spot = p[i]->getSpot();
					int col = p[i]->getColor();
					if (spot[0] == pos[0] && spot[1] == pos[1])
					{
						if (col == p[sel]->getColor())
						{
							valid = false;
							break;
						}
					}
				}
				if (valid)
				{
					m = {};
					m.push_back(pos[0]);
					m.push_back(pos[1]);
					moves.push_back(m);
				}
			}
			pos[0] = position[0];
			pos[1] = position[1];
			if (pos[0] > 0 && pos[1] < 7)
			{
				pos[0] -= 1;
				pos[1] += 1;
				valid = true;
				for (int i = 0; i < 32; i++)
				{
					if (i == sel)
						continue;
					int* spot = p[i]->getSpot();
					int col = p[i]->getColor();
					if (spot[0] == pos[0] && spot[1] == pos[1])
					{
						if (col == p[sel]->getColor())
						{
							valid = false;
							break;
						}
					}
				}
				if (valid)
				{
					m = {};
					m.push_back(pos[0]);
					m.push_back(pos[1]);
					moves.push_back(m);
				}
			}
			pos[0] = position[0];
			pos[1] = position[1];
			if (pos[1] < 7 && pos[0] < 7)
			{
				pos[1] += 1;
				pos[0] += 1;
				valid = true;
				for (int i = 0; i < 32; i++)
				{
					if (i == sel)
						continue;
					int* spot = p[i]->getSpot();
					int col = p[i]->getColor();
					if (spot[0] == pos[0] && spot[1] == pos[1])
					{
						if (col == p[sel]->getColor())
						{
							valid = false;
							break;
						}
					}
				}
				if (valid)
				{
					m = {};
					m.push_back(pos[0]);
					m.push_back(pos[1]);
					moves.push_back(m);
				}
			}
			pos[0] = position[0];
			pos[1] = position[1];
			if (pos[0] > 0 && pos[1] > 0)
			{
				pos[1] -= 1;
				pos[0] -= 1;
				valid = true;
				for (int i = 0; i < 32; i++)
				{
					if (i == sel)
						continue;
					int* spot = p[i]->getSpot();
					int col = p[i]->getColor();
					if (spot[0] == pos[0] && spot[1] == pos[1])
					{
						if (col == p[sel]->getColor())
						{
							valid = false;
							break;
						}
					}
				}
				if (valid)
				{
					m = {};
					m.push_back(pos[0]);
					m.push_back(pos[1]);
					moves.push_back(m);
				}
			}

		}
		return moves;
	}
};

