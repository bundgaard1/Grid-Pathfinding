#pragma once

#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <iostream>
#include <memory>
#include <vector>

#include "Cell.h"

typedef sf::Vector2u pos ;

class Grid {
   public:
    Grid(sf::Vector2u gridSize);
    sf::Vector2u Size();
    Cell* getCell(pos p);

   private:
   // std::vector<Cell> neighbors_for_cell(const Cell& cell);
    float heuristic(Cell a, Cell b);

    struct Size {
        uint cols;
        uint rows;
    } m_size;

    bool m_diagonals;

    // outer vector is x, inner vector is y
    std::vector<std::vector<Cell>> m_cells;
    pos m_start;
    pos m_end;
};
