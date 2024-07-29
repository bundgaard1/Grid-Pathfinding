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

    void setStart(Pos pos);
    void setEnd(Pos pos);

    Pos getStart() { return r_grid.getStart(); }
    Pos getEnd() { return r_grid.getEnd(); }


   private:
    Grid& r_grid;
    BaseSearch& r_search;
};