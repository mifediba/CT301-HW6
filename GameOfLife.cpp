    #include "GameOfLife.h"
    void GameOfLife::NextNGen(int gens){}
    void GameOfLife::RollBack(int gens){}
    void GameOfLife::PrintGame() const{}
    void GameOfLife::ToggleCell(int index){}
    void GameOfLife::ToggleCell(int row, int col){}
	//const std::string& GetCurrentGrid() const{}
    
    
    GameOfLife& GameOfLife::operator+=(int gens){
        if (gens >= 0){
            NextNGen(gens);
        }
        //else{
            //throw std::invalid_argument("Negative generation not permitted.\n");
        //}
        return *this;
    }
    GameOfLife& GameOfLife::operator-=(int gens){
        if (gens >= 0){
            RollBack(gens);
        }
        //else{
            //throw std::invalid_argument("Negative generation not permitted.\n");
        //}
        return *this;
    }
    GameOfLife& GameOfLife::operator++(){
        NextGen();
        return *this;
    }
    GameOfLife& GameOfLife::operator--(){
        RollBack(1);
        return *this;
    }
    std::shared_ptr<GameOfLife> GameOfLife::operator+(int gens) const{
        //if (gens > 0){
            std::shared_ptr<GameOfLife> newGOL = clone();
            (*newGOL).NextNGen(gens);
            return newGOL;
        //}
        //else{
            ;//throw std::invalid_argument("Negative generation not permitted.\n");
        //}  
    }
    std::shared_ptr<GameOfLife> GameOfLife::operator-(int gens) const{
        //if (gens > 0){
            std::shared_ptr<GameOfLife> newGOL = clone();
            (*newGOL).RollBack(gens);
            return newGOL;
        //}
        //else{
            //throw std::invalid_argument("Negative generation not permitted.\n");
        //}  
    }