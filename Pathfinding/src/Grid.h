#pragma once

#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <iostream>
#include <memory>
#include <vector>
#include "types.h"

#include "Cell.h"

class Grid {
   public:
    Grid(sf::Vector2i gridSize);
    sf::Vector2i Size();
    Cell* getCell(Pos p);
    Pos getStart() { return m_start; }
    Pos getEnd() { return m_end; }
    std::vector<Pos> neighbors_for_cell(Pos cell);

   private:
    bool cell_is_valid(Pos p);

    struct Size {
        int cols;
        int rows;
    } m_size;

    const Pos m_neighborDirs[4] = {
        {-1, 0},{0, -1}, {0, 1},  {1, 0},
    };

    bool m_diagonals;
    


    // outer vector is x, inner vector is y
    std::vector<std::vector<Cell>> m_cells;
    Pos m_start;
    Pos m_end;
};
