#pragma once

#include <SFML/Graphics.hpp>
#include <memory>
#include <vector>

typedef enum e_cell_state { Normal, Wall, Start, Goal} cell_state;

class Cell {
   public:
   Cell();
    Cell(int x, int y);

    int m_x, m_y;
    cell_state m_state;
};
