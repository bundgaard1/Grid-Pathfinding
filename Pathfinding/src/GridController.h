#pragma once

#include "Grid.h"

class GridController {
   public:
    GridController(Grid& grid);
    void reset();
    void clear();
    void pause();
    void diagonal();
    void try_again();

    void handleEvent(sf::Event& event);

    // Other control-related methods and properties
   private:
    Grid& m_grid;

    bool m_done = false;
    bool m_win = false;
    bool m_paused = true;
};