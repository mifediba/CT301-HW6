#ifndef GAMEOFLIFE_H
#define GAMEOFLIFE_H

#include <iostream>
#include <string>
#include <memory>

class GameOfLife{

public:
	//Copy constructor
//	GameOfLife(const GameOfLife&);
	//Assignment operator
//	GameOfLife& operator=(const GameOfLife&);

	//Mandatory public members
	//Virsual destructor
	virtual ~GameOfLife() = default;
	
	//Virtual functions
	virtual void NextGen() = 0;
	virtual void NextNGen(int gens);
	virtual void RollBack(int gens);
	virtual void PrintGame() const;
	virtual void ToggleCell(int index);
	virtual void ToggleCell(int row, int col);
	virtual std::shared_ptr<GameOfLife> clone() const = 0;
	GameOfLife& operator+=(int gens);
	GameOfLife& operator++();
	std::shared_ptr<GameOfLife> operator+(int gens) const;	
};

#endif //GAMEOFLIFE_H
