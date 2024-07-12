#pragma once

#include "Grid.h"
#include <vector>
#include <SFML/Graphics.hpp>
#include <memory>
#include <iostream>
#include <time.h>
#include <math.h>
#include <stdlib.h>

class UI
{
public:

	UI(sf::RenderWindow* window, sf::Font font, Grid* grid);
	void drawUI();

	sf::RenderWindow* m_window;
	Grid* m_grid;

	
	static constexpr float m_infoHeight = 40;
	static constexpr float m_y = 50;
	static constexpr float m_x = 1400;
	static constexpr int m_textSize = 26;
	const sf::Color m_textColor = sf::Color::White;
	sf::Font m_font;

};

