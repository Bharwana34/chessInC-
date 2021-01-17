#pragma once
#include <iostream>
#include <fstream>
#include "pieces.h"

using namespace std;


class DataBase
{
public:
	void saveData(Piece** p)
	{
		fstream file;
		file.open("data.txt" , ios::out);
		int* pos;
		for (int i = 0; i < 32; i++)
		{
			pos= p[i]->getSpot();
			file<< pos[0]<<pos[1] << p[i]->dead() <<endl;
		}
		file.close();
	}

	Piece** loadData()
	{
		Piece** p = new Piece * [32];
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
		
		fstream file;
		file.open("data.txt", ios::in);
		int i = 0 , d=0;
		int* spot = p[i]->getSpot();
		string data;
		while (!file.eof() && i<32)
		{
			file >> data;
			spot[0] = (int)(data[0]-'0');
			spot[1] = (int)(data[1]-'0');
			d = (int)(data[2]-'0');
			p[i]->setSpot(spot);
			if (d==1)
			{
				p[i]->captured();
			}
			i++;
		}
		return p;
	}
	void loadHelp()
	{
		fstream file;
		file.open("help.txt", ios::in);
		string data;
		int i = 0;
		while (!file.eof())
		{
			if (i % 15 == 0) cout << endl;
			file >> data ;
			cout << data << " ";
			i++;
		}
		cout << endl << endl;
	}
};
