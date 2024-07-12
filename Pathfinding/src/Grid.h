#pragma once

#include <vector>
#include <SFML/Graphics.hpp>
#include <memory>
#include <iostream>
#include <time.h>
#include <math.h>
#include <stdlib.h>

typedef enum cell_state {
	s_Normal,
	s_Open,
	s_Closed,
	s_Wall,
	s_Start,
	s_End,
	s_Path,
	s_size
} cell_state;

class Grid
{
public:
	class Cell;

	Grid(bool diagonals);
	void set_font(sf::Font font);
	void search();
	void draw_grid(sf::RenderWindow* ptr_window);
	void reset();
	void clear();
	void pause();
	void diagonal();
	void try_again();
	float heuristic(Cell a, Cell b);
	void make_ex4();

	static constexpr float m_cellSize = 120.0f;
	static const int m_rows = 10, m_cols = 10;
	bool m_diagonals;

	class Cell
	{
	public:
		Cell(int x, int y);
		void draw_cell(sf::RenderWindow* ptr_window, sf::Color col, sf::Font font);
		void add_neightbors(Grid* grid);


		int m_x, m_y;
		float m_f = 0, m_g = 0, m_h = 0;
		//  m_wall = false;
		std::vector<std::shared_ptr<Cell>> m_neightbors;
		std::shared_ptr<Cell> m_previous = NULL;

		cell_state m_state;
		int m_order;
	};

	std::vector<std::vector<std::shared_ptr<Cell>>> m_cells;
	std::vector<std::shared_ptr<Cell>> m_openSet;
	std::vector<std::shared_ptr<Cell>> m_closedSet;
	std::shared_ptr<Cell> m_start;
	std::shared_ptr<Cell> m_end;
	std::vector<std::shared_ptr<Cell>> m_path;
	bool m_done = false;
	bool m_win = false;
	bool m_paused = true;
	
	int m_order_added;
	sf::Font m_font;
};

