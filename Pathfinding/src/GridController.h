#pragma once

#include "Grid.h"
#include "GridSearchBase.h"

class GridController {
   public:
    GridController(Grid& grid, BaseSearch& search);
    void reset();
    void clear();
    void pause();
    void diagonal();
    void try_again();
    void handleEvent(sf::Event& event);

    // Other control-related methods and properties
   private:
    Grid& m_grid;
    BaseSearch& m_search;

    bool m_done = false;
    bool m_win = false;
    bool m_paused = true;
};