#pragma once
#include "Grid.h"

class Cell
{
public:
	Cell(int x, int y);
	void draw_cell(sf::RenderWindow* ptr_window);

private:
	Grid* ptr_grid;
	int m_x, m_y;
	float m_f, m_g, m_h;
	bool m_wall = false;

};


