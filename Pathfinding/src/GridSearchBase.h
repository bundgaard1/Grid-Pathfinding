#pragma once

#include "Grid.h"
#include "types.h"
#include <set>
#include <queue>

class BaseSearch {
    public:
        BaseSearch(Grid& grid) : m_grid(grid) {};
        virtual void init() = 0;
        virtual void search() = 0; 
        virtual void reset() = 0; 
        bool is_done() {
            return m_done;
        };

        virtual std::vector<Pos> get_openSet() = 0;
        virtual std::vector<Pos> get_closedSet() = 0;
        virtual std::vector<Pos> get_path() = 0;
    
    protected:
        Grid& m_grid;
        bool m_done = false;
};
