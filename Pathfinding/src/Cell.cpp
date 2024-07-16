#include "Cell.h"

Cell::Cell() {
    m_x = 0;
    m_y = 0;
    m_state = cell_state::Normal;
}

Cell::Cell(int x, int y) {
    m_x = x;
    m_y = y;

    cell_state tempState = cell_state::Normal;

    if ((rand() % 10) < 2) {
        tempState = cell_state::Wall;
    }
    m_state = tempState;
}

// void Cell::add_neightbors(Grid& grid) {
//     m_neightbors.clear();
//     // Left
//     if (m_x > 0) m_neightbors.push_back(grid.m_cells.at(m_x - 1).at(m_y));
//     // Up
//     if (m_y > 0) m_neightbors.push_back(grid.m_cells.at(m_x).at(m_y - 1));
//     // Right
//     if (m_x + 1 < grid.m_cols) m_neightbors.push_back(grid.m_cells.at(m_x + 1).at(m_y));
//     // Down
//     if (m_y + 1 < grid.m_rows) m_neightbors.push_back(grid.m_cells.at(m_x).at(m_y + 1));
//     if (grid.m_diagonals) {
//         // Up-Left
//         if (m_x > 0 && m_y > 0) m_neightbors.push_back(grid.m_cells.at(m_x - 1).at(m_y - 1));
//         // Up-Right
//         if (m_y > 0 && m_x + 1 < grid.m_cols) m_neightbors.push_back(grid.m_cells.at(m_x + 1).at(m_y - 1));
//         // Down-Left
//         if (m_y + 1 < grid.m_rows && m_x > 0) m_neightbors.push_back(grid.m_cells.at(m_x - 1).at(m_y + 1));
//         // Down-Right
//         if (m_y + 1 < grid.m_rows && m_x + 1 < grid.m_cols) m_neightbors.push_back(grid.m_cells.at(m_x + 1).at(m_y + 1));
//     }
// }