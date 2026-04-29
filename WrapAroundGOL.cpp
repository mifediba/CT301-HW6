#include "WrapAroundGOL.h"
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <stdexcept>

	//Constructor with filename input
	WrapAroundGOL::WrapAroundGOL(int width, int height, std::string grid): width(width), height(height), grid(grid), generation(0){
        std::string g;
        InputContentCheck(width, height, grid);
        g = GetGridDirect(grid);
        this->grid = g;
        //std::cout << "WrapAroundGOL test - width: " << width << ", height: " << height << ", grid: " << grid << std::endl;
    }
    std::shared_ptr<GameOfLife> makeWrapAround(int width, int height, std::string grid){
        return std::make_shared<WrapAroundGOL>(width, height, grid);
    }
    void WrapAroundGOL::NextGen(){
        int loopcounter = 0;
        int row, column;
        int nar, nac;
        int neighbor_row, neighbor_col;
        int num_live_neighbors = 0;
        int num_dead_neighbors = 0;
        int deltac, deltar;
        std::string neighbors = "ABC";
        std::string new_grid ="";
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
                        }
                        else{
                            neighbor_row = (neighbor_row + height) % height;
                            neighbor_col = (neighbor_col + width) % width;
                              if (grid.at((neighbor_row * width) + neighbor_col) == '0'){
                                num_dead_neighbors++; //count number of dead neighbors of current cell
                            }
                            else if (grid.at((neighbor_row * width) + neighbor_col) == '1'){
                                num_live_neighbors++; //count number of live neighbors of current cell
                            }
                        }
                    }
                }
            }
            if (t == '1' && (num_live_neighbors < 2 || num_live_neighbors > 3)){ //change current live cell value to dead if there are not exactly 2 living neighbors 
                new_grid += '0';
            }
            else if (t == '1' ){ //leave live cell value unchanged in cell has 2 living neighbors
                new_grid += '1';
            }
            else if (t == '0' && num_live_neighbors == 3){ //change dead cell value to live if have 3 living neighbors 
                new_grid += '1';
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

	void WrapAroundGOL::NextNGen(int gens){
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
	void WrapAroundGOL::PrintGame() const{
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
	void WrapAroundGOL::ToggleCell(int index){
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
	void WrapAroundGOL::ToggleCell(int row, int col){ 
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
    std::shared_ptr<GameOfLife> WrapAroundGOL::clone() const{
        return std::make_shared<WrapAroundGOL>(*this);
    }
    void WrapAroundGOL::InputContentCheck(int width, int height, std::string grid){
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
            if (c != 'O' && c != 'X'){
                throw std::invalid_argument("Invalid character in grid input.\n");
            }
        }
    }
    std::string WrapAroundGOL::GetGridDirect(std::string board){
        std::string grid;
        for (char c : board){
                if (c == 'X'){
                    grid += "0";
                }
                else if (c == 'O'){
                    grid += "1";
                }
            }
	    return grid;
    }