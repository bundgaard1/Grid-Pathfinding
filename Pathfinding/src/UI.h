#pragma once

#include <SFML/Graphics.hpp>

#include "GridController.h"
#include "GridView.h"

class UI {
   public:
    UI(GridController& gridCont, GridView& gridView, sf::Vector2f pos);
    void drawUI(sf::RenderWindow& windowReference);
    void handleEvent(sf::Event& event);

   private:
    // Text stuff
    void draw_text(sf::RenderWindow& windowReference, const sf::String text);
    void draw_backdrop_for_text(sf::RenderWindow& windowReference);
    bool load_font(const std::string& fontPath);

    sf::Vector2f m_pos;
    sf::Vector2f m_margin;
    float m_infoHeight;
    int m_text_count;

    sf::Font m_font;
    
    // Event handling
    void handleMouseEvent(sf::Event& event);
    void changeStateOfCellOnMouse(Pos pos);

    struct MouseState {
        bool isPressed = false;
        Pos lastPos;
        CellState stateChanging;
    } m_mouseState;

    // References 
    GridController& r_gridController;
    GridView& r_view;
    
};
