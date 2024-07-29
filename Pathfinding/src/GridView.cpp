#include "GridView.h"

GridView::GridView(Grid& grid, BaseSearch& search, sf::Vector2f viewport_size) : r_grid(grid), r_search(search),m_viewport_size(viewport_size) {
    auto grid_size = r_grid.Size();

    m_cell_size = m_viewport_size.x / grid_size.x;
}

void GridView::draw_grid(sf::RenderWindow& ptr_window) const  {
    auto grid_size = r_grid.Size();
    
    for (int i = 0; i < grid_size.x; i++) {
        for (int j = 0; j < grid_size.y; j++) {
            CellState currState = r_grid.getStateOfCell({i, j});
            draw_cell(ptr_window, {i,j}, m_cellColors.at(currState));
        }
    }

    draw_cell(ptr_window, r_grid.getStart(), sf::Color::Green);
    draw_cell(ptr_window, r_grid.getEnd()  , sf::Color::Red);

}

void GridView::draw_search(sf::RenderWindow& ptr_window) const  {
    auto open_cells = r_search.get_openSet();
    auto closed_cells = r_search.get_closedSet();

    for (auto cell : open_cells) {
        draw_point_on_cell(ptr_window, cell, sf::Color::Blue);
    }

    for (auto cell : closed_cells) {
        draw_point_on_cell(ptr_window, cell, sf::Color::Yellow);
    }

    if (r_search.is_done()) {
        auto path = r_search.get_path();
        for (int i = 0; i < path.size() - 1; i++) {
            draw_line_cell_to_cell(ptr_window, path[i], path[i + 1], sf::Color::Magenta);
        }
    }
    
}

void GridView::draw_cell(sf::RenderWindow& ptr_window, Pos pos, sf::Color color) const  {

    sf::RectangleShape rectCell({m_cell_size - 1, m_cell_size - 1});

    rectCell.setOutlineThickness(1);
    rectCell.setOutlineColor(sf::Color::Black);
    rectCell.setFillColor(color);
    rectCell.setPosition(sf::Vector2f(pos.x *m_cell_size + 1, pos.y * m_cell_size + 1));

    ptr_window.draw(rectCell);
}

void GridView::draw_point_on_cell(sf::RenderWindow& ptr_window, const Pos& pos, sf::Color color) const  {
    float circle_radius = m_cell_size /5;
    sf::CircleShape circle(circle_radius);

    circle.setFillColor(color);
    circle.setPosition(sf::Vector2f((pos.x) * m_cell_size, (pos.y) * m_cell_size ));
    sf::Vector2f move_to_center =circle.getPosition() + sf::Vector2f(m_cell_size /2 -circle_radius, m_cell_size /2 -circle_radius );
    circle.setPosition(move_to_center);

    ptr_window.draw(circle);
}


void GridView::draw_line_cell_to_cell(sf::RenderWindow& ptr_window, const Pos& start, const Pos& end, sf::Color color) const  {
    sf::Vertex line[] = {
        sf::Vertex(sf::Vector2f(start.x * m_cell_size + m_cell_size / 2, start.y * m_cell_size + m_cell_size / 2), color),
        sf::Vertex(sf::Vector2f(end.x * m_cell_size + m_cell_size / 2, end.y * m_cell_size + m_cell_size / 2), color)
    };
    

    ptr_window.draw(line, 2, sf::Lines);
} 


Pos GridView::cellPosFromViewportPosition(sf::Vector2i viewportPos) const  {
    auto grid_size = r_grid.Size();

    int x = viewportPos.x / m_cell_size;
    int y = viewportPos.y / m_cell_size;

    if (x < 0 || x >= grid_size.x || y < 0 || y >= grid_size.y) {
        return {-1, -1};
    }

    return {x, y};
}