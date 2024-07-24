#pragma once

#include "Grid.h"
#include "types.h"
#include <set>
#include <queue>

class Search {
    public:
        Search(Grid& grid);
        void init();
        void search(); 
        void reset(); 

        std::vector<Pos> get_openSet() ;
        std::vector<Pos> get_closedSet() ;

    private:
     Grid& m_grid;
     
    std::vector<Pos> m_openSet;
     std::vector<Pos> m_closedSet;


     
};
