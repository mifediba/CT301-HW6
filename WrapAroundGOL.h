#ifndef WRAPAROUNDGOL_H
#define WRAPAROUNDGOL_H
#include <iostream>
#include <string>
#include <memory>
#include "GameOfLife.h"

std::shared_ptr<GameOfLife> makeWrapAround(int width, int height, std::string grid);

class WrapAroundGOL : public GameOfLife{
    private: 
			int width;
		  int height;
		  std::string grid;
        
      int generation;
		  void InputContentCheck(int width, int height, std::string grid);
		  std::string GetGridDirect(std::string board);
    public:
        //Constructor
        WrapAroundGOL(int width, int height, std::string grid);
        //Copy constructor
        //ThreeStateGOL(const ThreeStateGOL&);
        //Assignment operator
        //ThreeStateGOL& operator=(const ThreeStateGOL&);
        //Mandatory public members
        void NextGen() override;
        void NextNGen(int gen) override;
        void PrintGame() const override;
        void ToggleCell(int index) override;
        void ToggleCell(int row, int col) override;
        std::shared_ptr<GameOfLife> clone() const override;
};
#endif //WRAPAROUNDGOL_H