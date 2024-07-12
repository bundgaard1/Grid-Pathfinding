#include "Grid.h"
#include <string>

Grid::Grid(bool diagonals) {
	m_diagonals = diagonals;
	m_order_added = 1;
	// Initialize Grid
	srand(time(NULL));
	for (int x = 0; x < m_cols; x++)
	{
		std::vector<std::shared_ptr<Cell>> bufferCol;
		for (int y = 0; y < m_rows; y++)
		{
			std::shared_ptr<Cell> rawCell (new Cell(x, y));
			bufferCol.push_back(rawCell);
		}
		m_cells.push_back(bufferCol);
	}
	

	// add neightbors
	for (int x = 0; x < m_cols; x++)
	{
		for (int y = 0; y < m_rows; y++)
		{
			m_cells.at(x).at(y)->add_neightbors(this);
		}
	}

	// Start and end
	m_start = m_cells.at(0).at(0);
	m_end = m_cells.at(m_rows - 1).at(m_cols - 1);
	m_start->m_state = s_Start;
	m_end->m_state = s_End;
	m_openSet.push_back(m_start);

	
}

void Grid::set_font(sf::Font font)  {
	m_font = font;
}

void Grid::search() {
	//if (m_paused)
	//	return;
	
	if (m_openSet.size() > 0 && !m_done)
	{
		// find next best
		int winner = 0;
		float bestFScore = INT32_MAX;
		// std::cout << m_openSet.size() << " ";
		for (int i = 0; i < m_openSet.size(); i++)
		{
			float currFScore = m_openSet.at(i).get()->m_f;
			if (currFScore <= bestFScore) {
				winner = i;
				bestFScore = currFScore;
			}
		}
		// std::cout << bestFScore << std::endl;

		std::shared_ptr<Cell> current(m_openSet.at(winner));

		// Check for end
		if (current == m_end) {
			std::cout << "DONE!" << std::endl;
			// make path
			std::shared_ptr<Cell> temp = current;
			m_done = true;
			m_win = true;
			while (temp != m_start)
			{
				if (temp->m_state != s_Start && temp->m_state != s_End)
					temp->m_state = s_Path;
				m_path.push_back(temp);
				temp = temp->m_previous;
			}
			
			return;
		}

		// move to closed set from open set
		m_closedSet.push_back(current);
		if (current->m_state != s_Start) current->m_state = s_Closed;
		
		m_openSet.erase(m_openSet.begin() + winner);

		std::vector<std::shared_ptr<Cell>> neighbors = current->m_neightbors;
		
		bool neighbor_added = false;
		
		// Go through every neighbor
		for (int i = 0; i < neighbors.size(); i++)
		{
			std::shared_ptr<Cell> neighbor = neighbors.at(i);
			if (neighbor->m_state == s_Closed || neighbor->m_state == s_Wall) {
				continue;
			}
			else {
				float tempG = current->m_g + heuristic(*current, *neighbor);
				bool newPath = false;
				if (neighbor->m_state == s_Open) {
					if (tempG < neighbor->m_g) {
						neighbor->m_g = tempG;
						newPath = true;
					} 
				}
				else
				{
					neighbor->m_g = tempG;
					
					neighbor_added = true;
					neighbor->m_order = m_order_added;
					m_openSet.push_back(neighbor);
					
					if(neighbor->m_state != s_Start && neighbor->m_state != s_End) 
						neighbor->m_state = s_Open;
					
					newPath = true;
				}

				if (newPath) {
					neighbor->m_h = heuristic(*m_end.get(), *neighbor.get());
					neighbor->m_f = neighbor->m_h + neighbor->m_g;
					neighbor->m_previous = current;
				}
			}

		}
		if (neighbor_added) m_order_added++;

	}
	else {
		// Stop, no solution
		m_done = true;
		m_paused = true;
		std::cout << "NO SOLUTION" << std::endl;
		
	}



	return;
}

float Grid::heuristic(Cell a, Cell b) {

	float dx = abs((float)(a.m_x) - (float)(b.m_x));
	float dy = abs((float)(a.m_y) - (float)(b.m_y));
	if (m_diagonals)
	{
		return sqrt(dx * dx + dy * dy);
	}
	else {
		return dx + dy;
	}
}

void Grid::draw_grid(sf::RenderWindow* ptr_window) {
	sf::Color colors[s_size] = {
		sf::Color::White,
		sf::Color(100, 100, 100),
		sf::Color(200, 200, 200),
		sf::Color::Black,
		sf::Color::Green,
		sf::Color::Red,
		sf::Color::Blue
	};

	for (int i = 0; i < m_cols; i++)
	{
		for (int j = 0; j < m_rows; j++)
		{
			std::shared_ptr<Cell> curr = m_cells.at(i).at(j);
			sf::Color col = colors[curr->m_state];
			curr.get()->draw_cell(ptr_window, col, m_font);
		}
	}
}

void Grid::reset() {
	srand(time(NULL));
	m_order_added = 1;

	m_cells.clear();
	m_openSet.clear();
	m_closedSet.clear();
	m_path.clear();

	for (int x = 0; x < m_cols; x++)
	{
		std::vector<std::shared_ptr<Cell>> bufferCol;
		for (int y = 0; y < m_rows; y++)
		{
			std::shared_ptr<Cell> rawCell(new Cell(x, y));
			bufferCol.push_back(rawCell);
		}
		m_cells.push_back(bufferCol);
	}


	// add neightbors
	for (int x = 0; x < m_cols; x++)
	{
		for (int y = 0; y < m_rows; y++)
		{
			m_cells.at(x).at(y)->add_neightbors(this);
		}
	}

	// Start and end
	m_start = m_cells.at(0).at(0);
	m_end = m_cells.at(m_rows - 1).at(m_cols - 1);
	m_start->m_state = s_Start;
	m_end->m_state = s_End;
	m_openSet.push_back(m_start);

	return;
}



void Grid::clear() {
	reset();
	for (int x = 0; x < m_cols; x++)
	{
		for (int y = 0; y < m_rows; y++)
		{
			std::shared_ptr<Cell> curr = m_cells.at(x).at(y);
			if (curr->m_state == s_Wall) {
				curr->m_state = s_Normal;
			}
		}
	}
}

void Grid::pause() {

	if (m_paused)
		m_paused = false;
	else 
		m_paused = true;
}

void Grid::try_again() {
	for (int x = 0; x < m_cols; x++)
	{
		for (int y = 0; y < m_rows; y++)
		{
			std::shared_ptr<Cell> curr = m_cells.at(x).at(y);
			if (curr->m_state == s_Closed || curr->m_state == s_Open || curr->m_state == s_Path) {
				curr->m_state = s_Normal;
			}
		}
	}
	m_closedSet.clear();
	m_openSet.clear();
	m_path.clear();
	
	m_done = false;
	m_win = false;
	m_paused = true;

	m_openSet.push_back(m_start);
}


void Grid::diagonal() {
	bool tempDia = m_diagonals;
	try_again();
	if (tempDia)
		m_diagonals = false;
	else
		m_diagonals = true;

	for (int x = 0; x < m_cols; x++)
	{
		for (int y = 0; y < m_rows; y++)
		{
			m_cells.at(x).at(y)->add_neightbors(this);
		}
	}
}

void Grid::make_ex4() {
	clear();

	m_start->m_state = s_Normal;
	m_end->m_state = s_Normal;
	m_start = m_cells[1][5];
	m_start->m_state = s_Start;
	m_end = m_cells[6][3];
	m_end->m_state = s_End;

	m_cells[2][2]->m_state = s_Wall;
	m_cells[2][3]->m_state = s_Wall;
	m_cells[3][3]->m_state = s_Wall;
	m_cells[4][3]->m_state = s_Wall;
	m_cells[5][3]->m_state = s_Wall;
	m_cells[5][4]->m_state = s_Wall;
	m_cells[3][5]->m_state = s_Wall;
	m_cells[5][6]->m_state = s_Wall;
	m_cells[5][7]->m_state = s_Wall;

	m_openSet.clear();
	m_openSet.push_back(m_start);

	return;
}

Grid::Cell::Cell(int x, int y) {
	m_x = x;
	m_y = y;
	m_f = 0.0f; 
	m_g = 0.0f; 
	m_h = 0.0f;

	cell_state tempState = s_Normal;
	
	if ((rand()%10) < 2) {
		tempState = s_Wall;
	}
	m_state = tempState;
}

void Grid::Cell::draw_cell(sf::RenderWindow* ptr_window, sf::Color col,sf::Font font ) {

	sf::RectangleShape rectCell(sf::Vector2f(Grid::m_cellSize - 1, Grid::m_cellSize - 1));

	rectCell.setOutlineThickness(1);
	rectCell.setOutlineColor(sf::Color::Black);
	rectCell.setFillColor(col);

	rectCell.setPosition(sf::Vector2f(m_x * Grid::m_cellSize + 1, m_y * Grid::m_cellSize + 1));
	ptr_window->draw(rectCell);

	// Draw text to text
	if (m_state == s_Open || m_state == s_Closed || m_state == s_Path) {
		sf::Text text;
		text.setFont(font);
		text.setCharacterSize(30);
		text.setFillColor(sf::Color::Black);
	
		// print g
		text.setPosition(sf::Vector2f((m_x+1) * Grid::m_cellSize - 30, m_y * Grid::m_cellSize + 1));
		text.setString(std::to_string((int)m_g));
		ptr_window->draw(text);
		// print h
		text.move({ 0, 40});
		text.setString(std::to_string((int)m_h));
		ptr_window->draw(text);
		// print f
		text.move({ 0, 40 });
		text.setStyle(sf::Text::Bold);
		text.setString(std::to_string((int)m_f));
		ptr_window->draw(text);

		// print order
		text.move({ -80, 0 });
		text.setStyle(sf::Text::Regular);
		text.setString(std::to_string((int)m_order));
		ptr_window->draw(text);

	}
}

void Grid::Cell::add_neightbors(Grid* grid) {
	m_neightbors.clear();
	// Left
	if (m_x > 0) m_neightbors.push_back(grid->m_cells.at(m_x - 1).at(m_y));
	// Up
	if (m_y > 0) m_neightbors.push_back(grid->m_cells.at(m_x).at(m_y - 1));
	// Right
	if (m_x + 1 < m_cols) m_neightbors.push_back(grid->m_cells.at(m_x + 1).at(m_y));
	// Down
	if (m_y + 1 < m_rows) m_neightbors.push_back(grid->m_cells.at(m_x).at(m_y + 1));
	if (grid->m_diagonals)
	{
		// Up-Left
		if (m_x > 0 && m_y > 0) m_neightbors.push_back(grid->m_cells.at(m_x - 1).at(m_y - 1));
		// Up-Right
		if (m_y > 0 && m_x + 1 < m_cols) m_neightbors.push_back(grid->m_cells.at(m_x + 1).at(m_y - 1));
		// Down-Left
		if (m_y + 1 < m_rows && m_x > 0) m_neightbors.push_back(grid->m_cells.at(m_x - 1).at(m_y + 1));
		// Down-Right
		if (m_y + 1 < m_rows && m_x + 1 < m_cols) m_neightbors.push_back(grid->m_cells.at(m_x + 1).at(m_y + 1));
	}

}