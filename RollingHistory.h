#ifndef ROLLINGHISTORY_H
#define ROLLINGHISTORY_H
#include<deque>
#include "GameOfLife.h"

class RollingHistory{
    private:
        std::deque<std::shared_ptr<GameOfLife>> history;
        size_t saveGens;
    public:
        RollingHistory(size_t saveGens);
        void AddGame(const std::shared_ptr<GameOfLife>& game);
        const std::deque<std::shared_ptr<GameOfLife>>& GetHistory() const;
    
};
#endif //ROLLINGHISTORY_H