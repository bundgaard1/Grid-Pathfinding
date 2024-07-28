#include "GridController.h" 

GridController::GridController(Grid& grid, BaseSearch& search) : r_grid(grid), r_search(search) {
    
}

void GridController::resetSearch() {
    srand(time(NULL));
    r_search.reset();
}

void GridController::clearGrid() {
    r_search.reset();

    sf::Vector2i size = r_grid.Size();
    for (int x = 0; x < size.x; x++) {
        for (int y = 0; y < size.y; y++) {
            auto a = r_grid.getCell({x, y});
            if (a->getState() != CellState::Start && a->getState() != CellState::Goal) {
                a->setState(CellState::Normal);
            }
        }
    }
}

void GridController::stepSearch() {
    r_search.search();
}

void GridController::setStateOfCell(Pos pos, CellState state) {
    try {
        r_grid.getCell(pos)->setState(state);
    } catch (std::out_of_range& e) {
        std::cout << "Out of range" << std::endl;
    } 
    r_search.reset();
}  

CellState GridController::getStateOfCell(Pos pos) {
    return r_grid.getCell(pos)->getState();
}
