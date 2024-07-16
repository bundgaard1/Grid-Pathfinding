#include "GridView.h"

GridView::GridView(Grid& grid, sf::Vector2f viewport_size) : m_grid(grid), m_viewport_size(viewport_size) {
    sf::Vector2u grid_size = m_grid.Size();

    m_cell_size = m_viewport_size.x / grid_size.x;
}

void GridView::draw_grid(sf::RenderWindow& ptr_window) const  {
    sf::Vector2u grid_size = m_grid.Size();
    
    for (uint i = 0; i < grid_size.x; i++) {
        for (uint j = 0; j < grid_size.y; j++) {
            const Cell* curr = m_grid.getCell({i, j});
            draw_cell(ptr_window, *curr);
        }
    }
}

void GridView::draw_cell(sf::RenderWindow& ptr_window, const Cell& cell) const  {
    cell_state state = cell.m_state;
    sf::Color col = m_colors.at(state);

    sf::RectangleShape rectCell({m_cell_size - 1, m_cell_size - 1});

    rectCell.setOutlineThickness(1);
    rectCell.setOutlineColor(sf::Color::Black);
    rectCell.setFillColor(col);

    rectCell.setPosition(sf::Vector2f(cell.m_x *m_cell_size + 1, cell.m_y * m_cell_size + 1));
    ptr_window.draw(rectCell);
}