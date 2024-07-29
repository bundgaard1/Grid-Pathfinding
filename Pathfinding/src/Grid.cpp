#include "Grid.h"

#include <string>

#include "Cell.h"

Grid::Grid(sf::Vector2i gridSize) : m_diagonals(false) {
    m_size = {gridSize.x, gridSize.y};

    srand(time(NULL));

    // Cells
    generate_cells(0.2);

    // Start and end
    m_start = {0,0};
    m_end = {m_size.cols - 1, m_size.rows - 1};
}

sf::Vector2i Grid::Size() { return sf::Vector2i(m_size.cols, m_size.rows); }

Cell* Grid::getCell(Pos p) {
    if (!cell_is_valid(p) ) {
        throw std::out_of_range("Index out of bounds: (" + std::to_string(p.x) + ", " + std::to_string(p.y) + ") < (" + std::to_string(m_size.cols) + ", " + std::to_string(m_size.rows) + ")");
    }

    return &m_cells[p.x][p.y];
}

CellState Grid::getStateOfCell(Pos pos) {
    try {
        return getCell(pos)->getState();
    } catch (std::out_of_range& e) {
        std::cout << e.what() << std::endl;
    }
    return CellState::Normal;
}

void Grid::setStateOfCell(Pos pos, CellState state) {
    if (pos == m_start || pos == m_end) {
        return;
    }
    try {
        getCell(pos)->setState(state);
    } catch (std::out_of_range& e) {
        std::cout << "Out of range, setter" << std::endl;
    } 
}

void Grid::setStart(Pos p) {
    if (getStateOfCell(p) == CellState::Wall) {
        return;
    }
    
    m_start = p;
}

void Grid::setEnd(Pos p) {
    if (getStateOfCell(p) == CellState::Wall) {
        return;
    }
    m_end = p;
}


std::vector<Pos> Grid::neighbors_for_cell(Pos cell) {
    std::vector<Pos> neighbors;

    for (int i = 0; i < 4; i++) {
        Pos neighbor_pos = {cell.x + m_neighborDirs[i].x, cell.y + m_neighborDirs[i].y};

        if (cell_is_valid(neighbor_pos) 
            && getCell(neighbor_pos)->getState() != CellState::Wall){
            neighbors.push_back(neighbor_pos);
        }
    }
    
    return neighbors;
}

bool Grid::cell_is_valid(Pos p) {
    return p.x >= 0 && p.x < m_size.cols && p.y >= 0 && p.y < m_size.rows;
}


void Grid::generate_cells(float cell_wall_chance) {

    m_cells.clear();
    m_cells.resize(m_size.cols, std::vector<Cell>(m_size.rows));

    for (int x = 0; x < m_size.cols; x++) {
        for (int y = 0; y < m_size.rows; y++) {
            CellState state = (rand() % 100 < cell_wall_chance * 100) 
                                ? CellState::Wall 
                                : CellState::Normal;
            Cell cell(x, y, state);
            m_cells[x][y] = cell;
        }
    }
}
