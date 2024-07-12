#include "UI.h"

UI::UI(sf::RenderWindow* window, sf::Font font, Grid* grid) {
	m_window = window;
	m_font = font;
	m_grid = grid;
}

void UI::drawUI() {
    sf::Text text;
    text.setFont(m_font);
    text.setCharacterSize(m_textSize);
    text.setFillColor(m_textColor);

    // C - clear
    text.setPosition({ m_x, m_y });
    text.setString("C: Clear");
    m_window->draw(text);

    // R - reset
    text.move({ 0, m_infoHeight });
    text.setString("R: Reset");
    m_window->draw(text);

    // T - Try again
    text.move({ 0, m_infoHeight });
    text.setString("T: Try again");
    m_window->draw(text);

    // D - Diagonals
    text.move({ 0, m_infoHeight });
    text.setString("D: Diagonals");
    m_window->draw(text);
    if (m_grid->m_diagonals)
        text.setString("On");
    else
        text.setString("Off");
    text.move({ 180, 0 });
    m_window->draw(text);
    text.move({ -180, 0 });

    // Space - pause
    text.move({ 0, m_infoHeight });
    text.setString("Space: ");
    m_window->draw(text);
    if (m_grid->m_paused)
        text.setString("Paused");
    else 
        text.setString("Running");
    text.move({ 100, 0 });
    m_window->draw(text);
    text.move({ -100, 0 });
}

void draw_text()