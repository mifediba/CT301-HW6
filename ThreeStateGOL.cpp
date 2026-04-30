#include "ThreeStateGOL.h"
#include "RollingHistory.h"
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <stdexcept>

	//Constructor with filename input
	ThreeStateGOL::ThreeStateGOL(int width, int height, std::string grid, size_t saveGens): width(width), height(height), grid(grid), saveGens(saveGens), generation(0){
        std::string g;
        InputContentCheck(width, height, grid);
        g = GetGridDirect(grid);
        this->grid = g;   
        //std::cout << "ThreeStateGOL test - width: " << width << ", height: " << height << ", grid: " << grid << std::endl;
    }
    std::shared_ptr<GameOfLife> makeThreeState(int width, int height, std::string grid, size_t saveGens){
        return std::make_shared<ThreeStateGOL>(width, height, grid, saveGens);
    }
    void ThreeStateGOL::NextGen(){
        int loopcounter = 0;
        int row, column;
        int nar, nac;
        int neighbor_row, neighbor_col;
        int num_live_neighbors = 0;
        int num_dead_neighbors = 0;
        std::string neighbors = "ABC";
        std::string new_grid ="";
        history.AddGame(std::make_shared<ThreeStateGOL>(*this));

        //std::cout << "Current grid: **" << grid << std::endl;
        for (char t : grid){//looping through each character in the grid
            row = loopcounter / width; //defining the width of the grid based on file width input
            column = loopcounter % width; //defining length of the grid based on file width input
            for (char nr : neighbors){ //neighbor row adjustment
                for (char nc : neighbors) {
                    if (nr == 'A' && nc == 'A'){//current cell
                        continue;
                    }
                    else{ //loop through 8 possible neighbor cell coordinates based on their proximity to current cell 
                        if (nr == 'A'){
                            nar = 0; //nar = neighbor adjusted row
                        }
                        else if (nr == 'B'){
                            nar = 1;
                        }
                        else if (nr == 'C'){
                            nar = -1;
                        }
                        if (nc == 'A') {
                            nac = 0; //nac = neighbor adjusted column
                        }
                        else if (nc == 'B'){
                            nac = 1;
                        }
                        else if (nc == 'C'){
                            nac = -1;
                        }
                        neighbor_row = row + nar; 
                        neighbor_col = column + nac;
                        if (neighbor_row > -1 && neighbor_row < height && neighbor_col > -1 && neighbor_col < width){ //only evaluate neighbors that can exist (non-zero, non-out-of-bounds)
                            if (grid.at((neighbor_row * width) + neighbor_col) == '0'){
                                num_dead_neighbors++; //count number of dead neighbors of current cell
                            }
                            else if (grid.at((neighbor_row * width) + neighbor_col) == '1'){
                                num_live_neighbors++; //count number of live neighbors of current cell
                            }
                            else if (grid.at((neighbor_row * width) + neighbor_col) == 'D'){
                                num_dead_neighbors++; //count decaying cell as dead
                            }
                        }
                    }
                }
            }
            if (t == '1' && (num_live_neighbors < 2 || num_live_neighbors > 4)){ //change current live cell value to decaying if there are not 2 or 3 living neighbors 
                new_grid += 'D';
            }
            else if (t == '1' ){ //leave live cell value unchanged in cell has 2 or 3 living neighbors
                new_grid += '1';
            }
            else if (t == 'D' && num_live_neighbors == 3){
                new_grid += '1'; //change decaying to live if 3 live neighbors
            }
            else if (t == 'D' && num_live_neighbors ==2){
                new_grid += 'D'; //dkecaying cell with exactly 2 live neightbors stays decaying
            }
            else if (t == 'D' && (num_live_neighbors < 2 || num_live_neighbors > 3)){
                new_grid += '0'; //decaying cell with any other live-neighbor count becomes dead
            }
            else if (t == '0' && num_live_neighbors == 3){ //change dead cell value to live if have 3 living neighbors 
                new_grid += 'D';
            }
            else {//keep dead cell dead if there are not 3 living cells around it **Might have to change this to catch incorrect grid input
                new_grid += '0';
            }
            loopcounter++;
            num_dead_neighbors = 0; //reset dead cell count
            num_live_neighbors = 0; //reset live cell count
        }
        //std::cout << "New grid: ***" << new_grid << std::endl;
        grid = new_grid; //replace current grid with newly calculated grid
        generation++; //increment up generation
    }
    void ThreeStateGOL::RollBack(int gens){
        for (int i = 0; i < gens; i++){
            //std::cout << generation << std::endl;
            //history.GetNewest()->PrintGame();
            grid = history.GetNewest()->GetCurrentGrid();
            history.RemoveNewest(gens);
          
           generation--;
        }
        //history.RemoveNewest(gens); 
        //std::cout << "Rollback successful" << std::endl;
        //history.PrintHistory(); 
       // NextGen();
///        grid = history.GetNewest()->GetCurrentGrid();
        //generation -= gens;
       // std::shared_ptr<GameOfLife> previousGame = history.GetNewest();
       // previousGame 
    }

	void ThreeStateGOL::NextNGen(int gens){
        if (gens > 0){
            for (int j = 0; j < gens; j++){
                NextGen();
            }
        }
        else if (gens == 0){
            return;
        }
        else{
            throw std::invalid_argument("Negative generation not allowed.\n");
        }
	}
	void ThreeStateGOL::PrintGame() const{
        int loopcounter = 0;
        std::cout << "Generation: " << generation << std::endl;
        for (char t : grid){
            loopcounter++;
            std::cout << t;
            if (loopcounter % width == 0){
                    std::cout <<"\n";
            }
        }
    }
	void ThreeStateGOL::ToggleCell(int index){
        int size = grid.size();;
        char cell = grid.at(index);
        if (index < 0 || index >= size){
            throw std::out_of_range("Index out of bounds.\n");
        }
        else{
            if (cell == '0'){
                grid.at(index) = '1';
            }
            else{
                grid.at(index) = '0';
            }
        } 
    }
	void ThreeStateGOL::ToggleCell(int row, int col){ 
        if (row < 0 || row >= height){
            throw std::out_of_range("Row input is out of bounds.\n");
        }
        else if (col < 0 || col >= width){
            throw std::out_of_range("Column input is out of bounds.\n");
        }
        else{
            int index = (row * width) + col;
            ToggleCell(index);
        }
    }
    const std::string& ThreeStateGOL::GetCurrentGrid() const{
        return grid;
    }
    std::shared_ptr<GameOfLife> ThreeStateGOL::clone() const{
        return std::make_shared<ThreeStateGOL>(*this);
    }
     void ThreeStateGOL::InputContentCheck(int width, int height, std::string grid){
        int size = grid.size();
        if (width <= 0 || height <= 0){
            throw std::invalid_argument("Invalid input dimensions.\n");
        }
        else if (size != width * height){
            throw std::invalid_argument("Invalid input dimensions.\n");
        }
        else if (size == 0){
            throw std::invalid_argument("Invalid grid.\n");
        }
        //Remove to check Toggle errors in grader.
        for (char c : grid){
            if (c != 'O' && c != 'X' && c != 'D'){
                throw std::invalid_argument("Invalid character in grid input.\n");
            }
        }
    }
    std::string ThreeStateGOL::GetGridDirect(std::string board){
        std::string grid;
        for (char c : board){
                if (c == 'X'){
                    grid += "0";
                }
                else if (c == 'O'){
                    grid += "1";
                }
                else if (c == 'D'){
                    grid += "D";
                }
            }
	    return grid;
    }