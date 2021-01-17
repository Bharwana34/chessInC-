#pragma once
#include <iostream>
#include <string>
#include "pieces.h"
#include "board.h"
#include "movement.h"
#include "database.h"

class Game
{
private:
	bool isEnd;
	Piece** p;
public:
	Game()
	{
		p = new Piece * [32];
		p[0] = new Pawn(WHITE, "11");
		p[1] = new Pawn(WHITE, "12");
		p[2] = new Pawn(WHITE, "13");
		p[3] = new Pawn(WHITE, "14");
		p[5] = new Pawn(WHITE, "15");
		p[6] = new Pawn(WHITE, "16");
		p[7] = new Pawn(WHITE, "17");
		p[8] = new Knight(WHITE, "01");				
		p[9] = new Knight(WHITE, "06");
		p[10] = new Bishop(WHITE, "02");          
		p[11] = new Bishop(WHITE, "05");
		p[12] = new King(WHITE, "03");			
		p[13] = new Queen(WHITE, "04");		
		p[14] = new Rock(WHITE, "00");			
		p[15] = new Rock(WHITE, "07");
		p[16] = new Pawn(BLACK, "60");
		p[17] = new Pawn(BLACK, "61");
		p[18] = new Pawn(BLACK, "62");
		p[19] = new Pawn(BLACK, "63");
		p[20] = new Pawn(BLACK, "64");
		p[21] = new Pawn(BLACK, "65");
		p[22] = new Pawn(BLACK, "66");
		p[23] = new Knight(BLACK, "71");
		p[24] = new Knight(BLACK, "76");
		p[25] = new Bishop(BLACK, "72");
		p[26] = new Bishop(BLACK, "75");
		p[27] = new King(BLACK, "73");
		p[28] = new Queen(BLACK, "74");
		p[29] = new Rock(BLACK, "70");
		p[30] = new Rock(BLACK, "77");
		p[4] = new Pawn(WHITE, "10");
		p[31] = new Pawn(BLACK, "67");
		isEnd = false;
	}
	void play(int load=0)
	{
		DataBase d;
		if (load != 0)
		{
			delete[] p;
			p = NULL;
			this->p = d.loadData();
		}
		color turn = WHITE;
		Board b(p);
		Move m(p, turn);				
		do
		{
			b.printLogo();
			b.draw();
			int sel = m.selectPiece();
			int* pos = p[sel]->getSpot();
			vector <vector <int>> pm = m.possibleMoves(sel, pos);
			system("CLS");
			b.printLogo();
			b.drawHints(pm);
			m.selectDestination(sel);
			d.saveData(p);
			this->checkEnd();
			system("CLS");

		} while (!this->isEnd);
	}
	void checkEnd()
	{
		if (p[27]->dead())
		{
			this->isEnd = true;
			cout << "<----------White WINS------------>\n";
			system("PAUSE");
		}
		else if (p[12]->dead())
		{
			this->isEnd = true;
			cout << "<------------BLACK wins----------->\n";
			system("PAUSE");
		}
	}

	void menuLoad()
	{
		system("CLS");
		Board b(p);
		DataBase d;
		b.printLogo();
		int choice;
		do
		{
			cout << "ENTER YOUR CHOICE \n";
			cout << "\tPRESS 1 To Start New Game\n";
			cout << "\tPress 2 to Load Previous Game\n";
			cout << "\tPress 3 to Load Help Document\n";
			cout << "\tPress 4 to quit\n";
			cin >> choice;
			if (choice < 1 || choice >4)
			{
				cout << "Invalid Choice Try again....\n";
			}
		} while (choice < 1 || choice>4);
		switch (choice)
		{
		case 1:
			system("CLS");
			play();
			break;
		case 2:
			system("CLS");
			play(1);
			break;
		case 3:
			cout << "HERE IS HELP FOR CHESS GAME\n";
			d.loadHelp();
			system("PAUSE");
			this->menuLoad();
			break;
		case 4:
			cout << "GAME ENDED BY YOUR CHOICE\n";
			break;
		
		}
	}
};
