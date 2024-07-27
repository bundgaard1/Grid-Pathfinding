#include "Cell.h"

Cell::Cell() {
    m_pos = Pos(0, 0);
    m_state = CellState::Normal;
}

Cell::Cell(int x, int y, CellState state) {
    m_pos = Pos(x, y);
    m_state = state;
}

Pos Cell::getPos() const {
    return m_pos;
}   

CellState Cell::getState() const {
    return m_state;
}

void Cell::setState(CellState state) {
    m_state = state;
} 

