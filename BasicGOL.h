#ifndef BASICGOL_H
#define BASICGOL_H
#include <iostream>
#include <string>
#include <memory>

#include "GameOfLife.h"

std::shared_ptr<GameOfLife> makeStandard(int width, int height, std::string grid);
class BasicGOL : public GameOfLife{
	private: 
		int width;
		int height;
		std::string grid;
        
        int generation;
		void InputContentCheck(int width, int height, std::string grid);
		std::string GetGridDirect(std::string board);

	public:
		//Constructor
		BasicGOL(int width, int height, std::string grid);
		void NextGen() override;
		void NextNGen(int gen) override;
		void PrintGame() const override;
		void ToggleCell(int index) override;
		void ToggleCell(int row, int col) override;

		std::shared_ptr<GameOfLife> clone() const override;
};
#endif //BASICGO_H