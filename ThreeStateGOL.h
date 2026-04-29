#ifndef THREESTATEGOL_H
#define THREESTATEGOL_H
#include <iostream>
#include <string>
#include <memory>
#include "GameOfLife.h"

std::shared_ptr<GameOfLife> makeThreeState(int width, int height, std::string grid);

class ThreeStateGOL : public GameOfLife{
    private: 
			int width;
		  int height;
		  std::string grid;
        
      int generation;
		  void InputContentCheck(int width, int height, std::string grid);
		  std::string GetGridDirect(std::string board);
    public:
        //Constructor
        ThreeStateGOL(int width, int height, std::string grid);
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
#endif //THREESTATEGOL_H