#ifndef WRAPAROUNDGOL_H
#define WRAPAROUNDGOL_H
#include <iostream>
#include <string>
#include <memory>
#include "GameOfLife.h"

std::shared_ptr<GameOfLife> makeWrapAround(int width, int height, std::string grid, size_t saveGens = 100);

class WrapAroundGOL : public GameOfLife{
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
        WrapAroundGOL(int width, int height, std::string grid, size_t saveGens = 100);
        //Copy constructor
        //ThreeStateGOL(const ThreeStateGOL&);
        //Assignment operator
        //ThreeStateGOL& operator=(const ThreeStateGOL&);
        //Mandatory public members
        void NextGen() override;
        void RollBack(int gens) override;
        void NextNGen(int gens) override;
        void PrintGame() const override;
        void ToggleCell(int index) override;
        void ToggleCell(int row, int col) override;
        std::shared_ptr<GameOfLife> clone() const override;
};
#endif //WRAPAROUNDGOL_H