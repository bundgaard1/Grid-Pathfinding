#include <SFML/Graphics.hpp>

#include "Cell.h"
#include "Grid.h"

class GridView {
   public:
    GridView(Grid& grid, sf::Vector2f viewport_size);
    void    draw_grid(sf::RenderWindow& ptr_window) const;
    void    draw_cell(sf::RenderWindow& ptr_window, const Cell& cell) const;

   private:
    Grid& m_grid;
    sf::Vector2f m_viewport_size;
    float m_cell_size;

    const std::map<cell_state, sf::Color> m_colors = {
        {cell_state::Normal, sf::Color::White}, {cell_state::Wall, sf::Color::Black},
        {cell_state::Start, sf::Color::Green},  {cell_state::Goal, sf::Color::Red},
    };
};
