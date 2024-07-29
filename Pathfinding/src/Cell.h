#pragma once

#include <SFML/Graphics.hpp>
#include <memory>
#include <vector>
#include "Pos.h"

enum class CellState { Normal, Wall} ;

class Cell {
   public:
    Cell();
    Cell(int x, int y, CellState state);
    Pos getPos() const;
    CellState getState() const;
    void setState(CellState state);

   private:
    Pos m_pos;
    CellState m_state;
    

};
