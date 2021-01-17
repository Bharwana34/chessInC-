#pragma once
#include <iostream>
#include <string>

enum color{BLACK , WHITE};
class Piece
{
private:
	int *spot;
	color col;
	bool isOccupied;
public:
	Piece(color c, std::string s)
	{
		spot = new int[2];
		spot[0] = (int)s[0]-'0';
		spot[1] = (int)s[1]-'0';
		this->col = c;
		isOccupied = false;
	}
	void occ()
	{
		spot[0] = 9;
		spot[1] = 9;
		this->isOccupied = true;
	}
	virtual void captured()
	{
		this->occ();
	}
	virtual char getType()
	{
		return 'O';
	}
	int* gets()
	{
		int* a = new int[2];
		a[0] = spot[0];
		a[1] = spot[1];
		return a;
	}
	color getc()
	{
		return this->col;
	}
	virtual int* getSpot()
	{
		return this->spot;
	}
	virtual int getColor()
	{
		return this->col;
	}
	bool d()
	{
		return this->isOccupied;
	}
	virtual bool dead()
	{
		return this->d();
	}
	void ss(int* sp)
	{
		this->spot[0] = sp[0];
		this->spot[1] = sp[1];
	}
	virtual void setSpot(int* dSpot)
	{
		ss(dSpot);
	}
	virtual bool isStart()
	{
		return true;
	}
	virtual void used()
	{}
	~Piece()
	{
		delete[] spot;
		spot = NULL;
	}
};

class Pawn : public Piece
{
private:
	char type;
	bool start;
public:
	Pawn(color c, std::string s) :Piece(c, s)
	{
		this->type = 'P';
		start = true;
	}
	bool isStart()
	{
		return this->start;
	}
	void used()
	{
		this->start = false;
	}
	char getType()
	{
		return this->type;
	}
	int* getSpot()
	{
		return this->gets();
	}
	int getColor()
	{
		return this->getc();
	}
	void captured()
	{
		this->occ();
	}
	bool dead()
	{
		return this->d();
	}
};

class Knight : public Piece
{
private:
	char type;
public:
	Knight(color c, std::string s) :Piece(c, s)
	{
		this->type = 'N';
	}
	char getType()
	{
		return this->type;
	}
	int* getSpot()
	{
		return this->gets();
	}
	int getColor()
	{
		return this->getc();
	}
	void captured()
	{
		this->occ();
	}
	bool dead()
	{
		return this->d();
	}
	void setSpot(int* dSpot)
	{
		ss(dSpot);
	}
};

class Bishop : public Piece
{
private:
	char type;
public:
	Bishop(color c, std::string s) :Piece(c, s)
	{
		this->type = 'B';
	}
	char getType()
	{
		return this->type;
	}
	int* getSpot()
	{
		return this->gets();
	}
	int getColor()
	{
		return this->getc();
	}
	void captured()
	{
		this->occ();
	}
	bool dead()
	{
		return this->d();
	}
	void setSpot(int* dSpot)
	{
		ss(dSpot);
	}
};

class Queen : public Piece
{
private:
	char type;
public:
	Queen(color c, std::string s) :Piece(c, s)
	{
		this->type = 'Q';
	}
	char getType()
	{
		return this->type;
	}
	int* getSpot()
	{
		return this->gets();
	}
	int getColor()
	{
		return this->getc();
	}
	void captured()
	{
		this->occ();
	}
	bool dead()
	{
		return this->d();
	}
	void setSpot(int* dSpot)
	{
		ss(dSpot);
	}
};

class Rock : public Piece
{
private:
	char type;
public:
	Rock(color c, std::string s) :Piece(c, s)
	{
		this->type = 'R';
	}
	char getType()
	{
		return this->type;
	}
	int* getSpot()
	{
		return this->gets();
	}
	int getColor()
	{
		return this->getc();
	}
	void captured()
	{
		this->occ();
	}
	bool dead()
	{
		return this->d();
	}
	void setSpot(int* dSpot)
	{
		ss(dSpot);
	}
};

class King : public Piece
{
private:
	char type;
public:
	King(color c, std::string s) :Piece(c, s)
	{
		this->type = 'K';
	}
	char getType()
	{
		return this->type;
	}
	int* getSpot()
	{
		return this->gets();
	}
	int getColor()
	{
		return this->getc();
	}
	void captured()
	{
		this->occ();
	}
	bool dead()
	{
		return this->d();
	}
	void setSpot(int* dSpot)
	{
		ss(dSpot);
	}
};