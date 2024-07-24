#include "GridView.h"

GridView::GridView(Grid& grid, Search& search, sf::Vector2f viewport_size) : m_grid(grid), m_search(search),m_viewport_size(viewport_size) {
    auto grid_size = m_grid.Size();

    m_cell_size = m_viewport_size.x / grid_size.x;
}

void GridView::draw_grid(sf::RenderWindow& ptr_window) const  {
    auto grid_size = m_grid.Size();
    
    for (int i = 0; i < grid_size.x; i++) {
        for (int j = 0; j < grid_size.y; j++) {
            const Cell* curr = m_grid.getCell({i, j});
            draw_cell(ptr_window, *curr);
        }
    }
}

void GridView::draw_search(sf::RenderWindow& ptr_window) const  {
    auto  open_cells = m_search.get_openSet();
    auto closed_cells = m_search.get_closedSet();

    for (auto cell : open_cells) {
        draw_point_on_cell(ptr_window, cell, sf::Color::Blue);
    }

    for (auto cell : closed_cells) {
        draw_point_on_cell(ptr_window, cell, sf::Color::Yellow);
    }
    
}

void GridView::draw_cell(sf::RenderWindow& ptr_window, const Cell& cell) const  {
    cell_state state = cell.m_state;
    sf::Color col = m_cellColors.at(state);

    sf::RectangleShape rectCell({m_cell_size - 1, m_cell_size - 1});

    rectCell.setOutlineThickness(1);
    rectCell.setOutlineColor(sf::Color::Black);
    rectCell.setFillColor(col);
    rectCell.setPosition(sf::Vector2f(cell.m_x *m_cell_size + 1, cell.m_y * m_cell_size + 1));

    ptr_window.draw(rectCell);
}

void GridView::draw_point_on_cell(sf::RenderWindow& ptr_window, const Pos& pos, sf::Color color) const  {
    sf::CircleShape circle(m_cell_size /4);

    circle.setFillColor(color);
    circle.setPosition(sf::Vector2f((pos.x) * m_cell_size, (pos.y) * m_cell_size ));

    ptr_window.draw(circle);
}

