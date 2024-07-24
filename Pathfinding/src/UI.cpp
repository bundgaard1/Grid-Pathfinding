#include "UI.h"

#include <math.h>
#include <stdlib.h>
#include <time.h>

#include <iostream>
#include <memory>
#include <vector>

UI::UI(GridController& gridCont, sf::Vector2f pos) : m_gridController(gridCont), m_pos(pos) {
    m_margin = {50, 50};
    m_infoHeight = 40.0f;
    m_text_count = 0;

    load_font("resources/fonts/Raleway-Regular.ttf");
}

void UI::drawUI(sf::RenderWindow& window) {
    m_text_count = 0;

    draw_text(window, "C: Clear");
    draw_text(window, "R: Reset");
    draw_text(window, "T: Try again");

    // draw_text(window, text, m_grid.m_diagonals ? "On" : "Off", {m_x + 180, m_y + 3 * m_infoHeight});

    // Space - pause
    // const sf::String ptext = m_grid.m_paused ? "Paused" : "Running";
    // draw_text(window,text, "Space: " + ptext, {m_x, m_y + 4 * m_infoHeight});
}

void UI::draw_text(sf::RenderWindow& window, const sf::String s) {
    sf::Text sf_text;
    sf_text.setFont(m_font);
    sf_text.setCharacterSize(26);
    sf_text.setFillColor(sf::Color::White);
    sf_text.setPosition(m_pos + m_margin + (sf::Vector2f){0, m_text_count * m_infoHeight}) ;
    sf_text.setString(s);
    window.draw(sf_text);
    m_text_count++;
}

bool UI::load_font(const std::string& fontPath) {
    if (!m_font.loadFromFile(fontPath)) {
        std::cerr << "Failed to load font: " << fontPath << std::endl;
        return false;
    }
    return true;
}