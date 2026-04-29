#include "RollingHistory.h"

RollingHistory::RollingHistory(size_t saveGens): saveGens(saveGens){} 

void RollingHistory::AddGame(const std::shared_ptr<GameOfLife>& game){
    history.push_back(game);
    if (history.size() > saveGens){
        history.pop_front();
    }
}
