#pragma once

#include <SFML/Graphics.hpp>

#include "GridController.h"

class UI {
   public:
    UI(GridController& gridCont, sf::Vector2f pos);
    void drawUI(sf::RenderWindow& window);

   private:
    void draw_text(sf::RenderWindow& window, const sf::String text);
    bool load_font(const std::string& fontPath);

    GridController& m_gridController;
    sf::Vector2f m_pos;
    sf::Vector2f m_margin;


    float m_infoHeight;
    int m_text_count;

    sf::Font m_font;
};
