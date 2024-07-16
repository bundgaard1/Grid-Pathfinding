#include "Grid.h"

#include <string>

#include "Cell.h"

Grid::Grid(sf::Vector2u gridSize) : m_diagonals(false) {
    m_diagonals = false;
    m_size = {gridSize.x, gridSize.y};

    srand(time(NULL));

    // Cells
    m_cells.resize(m_size.cols, std::vector<Cell>(m_size.rows));

    for (int x = 0; x < m_size.cols; x++) {
        for (int y = 0; y < m_size.rows; y++) {
            Cell rawCell(x, y);
            m_cells[x][y] = rawCell;
        }
    }

    // Start and end
    m_start = {0,0};
    m_end = {m_size.cols - 1, m_size.rows - 1};
    getCell(m_start)->m_state = cell_state::Start;
    getCell(m_end)->m_state = cell_state::Goal;
}

sf::Vector2u Grid::Size() { return sf::Vector2u(m_size.cols, m_size.rows); }


float Grid::heuristic(Cell a, Cell b) {
    float dx = abs((float)(a.m_x - b.m_x));
    float dy = abs((float)(a.m_y - b.m_y));
    if (m_diagonals) {
        return sqrt(dx * dx + dy * dy);
    } else {
        return dx + dy;
    }
}


Cell* Grid::getCell(pos p) {
    if (p.x < 0 || p.x >= m_size.cols || p.y < 0 || p.y >= m_size.rows) {
        throw std::out_of_range("Index out of bounds");
    }

    return &m_cells[p.x][p.y];
}

