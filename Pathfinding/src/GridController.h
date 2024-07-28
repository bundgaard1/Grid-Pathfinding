#pragma once

#include "Grid.h"
#include "GridSearchBase.h"

class GridController {
   public:
    GridController(Grid& grid, BaseSearch& search);
    
    void resetSearch();
    void clearGrid();
    void stepSearch();

    void setStateOfCell(Pos pos, CellState state);
    CellState getStateOfCell(Pos pos);


   private:
    Grid& r_grid;
    BaseSearch& r_search;
};