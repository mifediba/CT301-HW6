#include "RollingHistory.h"

RollingHistory::RollingHistory(size_t saveGens): saveGens(saveGens){} 

void RollingHistory::AddGame(const std::shared_ptr<GameOfLife>& game){   
    if (history.size() >= saveGens){
        history.pop_front();
    }
    history.push_back(std::move(game));
}

std::shared_ptr<GameOfLife> RollingHistory::GetNewest() const{
    if (history.empty()){
        std::cout << "No games in history.\n";
        return nullptr;
    }
    else{
        return history.back();
    }
}
std::shared_ptr<GameOfLife> RollingHistory::GetOldest() const{
    if (history.empty()){
        std::cout << "No games in history.\n";
        return nullptr;
    }
    else{
        return history.front();
    }
}
//void RollingHistory::print(std::shared_ptr<GameOfLife> game) const{
//    game->PrintGame();
//}
    
//const std::deque<std::shared_ptr<GameOfLife>>& RollingHistory::PrintHistory() const{

void RollingHistory::PrintHistory() const{
    for (const std::shared_ptr<GameOfLife>& game : history){
        game->PrintGame();
    }
}

//void RollingHistory::print(std::shared_ptr<GameOfLife> game) const{
//    game->PrintGame();
//}

