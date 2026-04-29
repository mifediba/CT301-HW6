#ifndef BASICGOL_H
#define BASICGOL_H
#include <iostream>
#include <string>
#include <memory>

#include "GameOfLife.h"

std::shared_ptr<GameOfLife> makeStandard(int width, int height, std::string grid, size_t saveGens = 100);
class BasicGOL : public GameOfLife{
	private: 
		int width;
		int height;
		std::string grid;
		size_t saveGens;
        
        int generation;
		void InputContentCheck(int width, int height, std::string grid);
		std::string GetGridDirect(std::string board);

	public:
		//Constructor
		BasicGOL(int width, int height, std::string grid, size_t saveGens = 100);
		void NextGen() override;
		void RollBack(int gens) override;
		void NextNGen(int gens) override;
		void PrintGame() const override;
		void ToggleCell(int index) override;
		void ToggleCell(int row, int col) override;

		std::shared_ptr<GameOfLife> clone() const override;
};
#endif //BASICGO_H