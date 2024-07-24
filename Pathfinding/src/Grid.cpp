#include "Grid.h"

#include <string>

#include "Cell.h"

Grid::Grid(sf::Vector2i gridSize) : m_diagonals(false) {
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

sf::Vector2i Grid::Size() { return sf::Vector2i(m_size.cols, m_size.rows); }

Cell* Grid::getCell(Pos p) {
    if (p.x < 0 || p.x >= m_size.cols || p.y < 0 || p.y >= m_size.rows) {
        throw std::out_of_range("Index out of bounds");
    }

    return &m_cells[p.x][p.y];
}

std::vector<Pos> Grid::neighbors_for_cell(Pos cell) {
    std::vector<Pos> neighbors;

    for (int i = 0; i < 4; i++) {
        Pos neighbor = {cell.x + m_neighborDirs[i].x, cell.y + m_neighborDirs[i].y};

        if (cell_is_valid(neighbor) 
            && getCell(neighbor)->m_state != cell_state::Wall){
            neighbors.push_back(neighbor);
        }
    }
    

    return neighbors;
}

bool Grid::cell_is_valid(Pos p) {
    return p.x >= 0 && p.x < m_size.cols && p.y >= 0 && p.y < m_size.rows;
}



