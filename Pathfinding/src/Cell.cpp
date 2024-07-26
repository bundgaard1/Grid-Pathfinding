#include "Cell.h"

Cell::Cell() {
    m_x = 0;
    m_y = 0;
    m_state = cell_state::Normal;
}

Cell::Cell(int x, int y, cell_state state) {
    m_x = x;
    m_y = y;
    m_state = state;
}


