#include "RollingHistory.h"

RollingHistory::RollingHistory(size_t saveGens): saveGens(saveGens){} 

void RollingHistory::AddGame(const std::shared_ptr<GameOfLife>& game){   
    if (history.size() > saveGens){
        history.pop_front();
    }
    history.push_back(game);
}
const std::deque<std::shared_ptr<GameOfLife>>& RollingHistory::GetHistory() const{
    return history;
}
