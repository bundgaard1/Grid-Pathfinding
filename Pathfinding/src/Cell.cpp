#include "Cell.h"

Cell::Cell(int x, int y) {
	m_x = x;
	m_y = y;

	if (x + y % 6 == 0)
	{
		m_wall = true;
	}

}

void Cell::draw_cell(sf::RenderWindow* ptr_window) {
	sf::RectangleShape rectCell(sf::Vector2f(Grid::m_cellSize-1, Grid::m_cellSize-1));
	
	sf::Color col = sf::Color::White;
	if (m_wall) col = sf::Color::Green;
	rectCell.setOutlineThickness(1);
	rectCell.setPosition(sf::Vector2f(m_x * Grid::m_cellSize, m_y * Grid::m_cellSize));
	ptr_window->draw(rectCell);

}