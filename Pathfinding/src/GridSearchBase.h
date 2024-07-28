#pragma once

#include "Grid.h"
#include "Pos.h"
#include <set>
#include <queue>

class BaseSearch {
    public:
        BaseSearch(Grid& grid) : r_grid(grid) {};
        virtual void search() = 0; 
        virtual void reset() = 0; 
        bool is_done() {
            return m_done;
        };

        virtual std::vector<Pos> get_openSet() = 0;
        virtual std::vector<Pos> get_closedSet() = 0;
        virtual std::vector<Pos> get_path() = 0;
    
    protected:
        virtual void init() = 0;
        Grid& r_grid;
        bool m_done = false;
};
