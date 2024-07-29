#include "GridController.h" 

GridController::GridController(Grid& grid, BaseSearch& search) : r_grid(grid), r_search(search) {
    
}

void GridController::resetSearch() {
    r_search.reset();
}

void GridController::clearGrid() {
    r_search.reset();

    sf::Vector2i size = r_grid.Size();
    for (int x = 0; x < size.x; x++) {
        for (int y = 0; y < size.y; y++) {
            r_grid.setStateOfCell({x, y}, CellState::Normal);
        }
    }
}

void GridController::stepSearch() {
    r_search.search();
}

void GridController::setStateOfCell(Pos pos, CellState state) {
    try {
        r_grid.setStateOfCell(pos, state);
    } catch (std::out_of_range& e) {
        std::cout << "Out of range, from controller" << std::endl;
    } 
    r_search.reset();
}  

CellState GridController::getStateOfCell(Pos pos) {
    try {
        return r_grid.getStateOfCell(pos);
    } catch (std::out_of_range& e) {
        std::cout << "Out of range, from controller" << std::endl;
    }
    return CellState::Normal;
}

void GridController::setStart(Pos pos) {
    r_grid.setStart(pos);
    r_search.reset();
}

void GridController::setEnd(Pos pos) {
    r_grid.setEnd(pos);
    r_search.reset();
}
