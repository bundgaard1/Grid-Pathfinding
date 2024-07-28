#pragma once

#include <SFML/Graphics.hpp>

#include "Cell.h"
#include "Grid.h"
#include "GridSearchBase.h"

class GridView {
   public:
    GridView(Grid& grid, BaseSearch& search, sf::Vector2f viewport_size);
    void    draw_grid(sf::RenderWindow& windowReference) const;
    void    draw_search(sf::RenderWindow& windowReference) const;
    
    Pos cellPosFromViewportPosition(sf::Vector2i viewportPos) const;

   private:
    void    draw_cell(sf::RenderWindow& windowReference, const Cell& cell) const;
    void    draw_point_on_cell(sf::RenderWindow& windowReference, const Pos& pos, sf::Color color) const;
    void    draw_line_cell_to_cell(sf::RenderWindow& windowReference, const Pos& start, const Pos& end, sf::Color color) const;

    Grid& r_grid;
    BaseSearch& r_search;
    sf::Vector2f m_viewport_size;
    float m_cell_size;

    const std::map<CellState, sf::Color> m_cellColors = {
        {CellState::Normal, sf::Color::White}, {CellState::Wall, sf::Color::Black},
        {CellState::Start, sf::Color::Green},  {CellState::Goal, sf::Color::Red},
    };
};
