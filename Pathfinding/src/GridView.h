#pragma once

#include <SFML/Graphics.hpp>

#include "Cell.h"
#include "Grid.h"
#include "GridSearch.h"

class GridView {
   public:
    GridView(Grid& grid, Search& search, sf::Vector2f viewport_size);
    void    draw_grid(sf::RenderWindow& ptr_window) const;
    void    draw_search(sf::RenderWindow& ptr_window) const;

   private:
    void    draw_cell(sf::RenderWindow& ptr_window, const Cell& cell) const;
    void    draw_point_on_cell(sf::RenderWindow& ptr_window, const Pos& pos, sf::Color color) const;

    Grid& m_grid;
    Search& m_search;
    sf::Vector2f m_viewport_size;
    float m_cell_size;

    const std::map<cell_state, sf::Color> m_cellColors = {
        {cell_state::Normal, sf::Color::White}, {cell_state::Wall, sf::Color::Black},
        {cell_state::Start, sf::Color::Green},  {cell_state::Goal, sf::Color::Red},
    };
};
