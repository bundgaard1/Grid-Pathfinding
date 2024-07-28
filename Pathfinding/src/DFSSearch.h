#pragma once

#include "Grid.h"
#include "Pos.h"
#include "GridSearchBase.h"
#include <set>
#include <queue>
#include <map>


class DFSSearch : public BaseSearch {
   public:
    DFSSearch(Grid& grid) : BaseSearch(grid) {
        init();
    };
    void search() override; 
    void reset() override; 

    std::vector<Pos> get_openSet() override;
    std::vector<Pos> get_closedSet()override ;
    std::vector<Pos> get_path() override;

    private:
     void init() override;
     
     std::vector<Pos> m_openSet;
     std::vector<Pos> m_closedSet;
     std::map<Pos, Pos> m_cameFrom;
};
