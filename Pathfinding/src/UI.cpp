#include "UI.h"

#include <math.h>
#include <stdlib.h>
#include <time.h>

#include <iostream>
#include <memory>
#include <vector>

UI::UI(GridController& gridCont,  GridView& gridView,  sf::Vector2f pos) : r_gridController(gridCont), r_view(gridView), m_pos(pos) {
    m_margin = {50, 50};
    m_infoHeight = 40.0f;
    m_text_count = 0;

    

    load_font("resources/fonts/Raleway-Regular.ttf");
}

void UI::handleEvent(sf::Event& event) {
    if (event.type == sf::Event::KeyPressed) {
        switch (event.key.code) {
            case (sf::Keyboard::R):
                r_gridController.resetSearch();
                break;
            case (sf::Keyboard::C):
                r_gridController.clearGrid();
                break;
            case (sf::Keyboard::Space):
                r_gridController.stepSearch();
                break;
            default:
                break;
        }
    }
    
    if (event.type == sf::Event::MouseButtonPressed) {
        m_mouseState.isPressed = true;
        m_mouseState.stateChanging = r_gridController.getStateOfCell(m_mouseState.lastPos);
        changeStateOfCellOnMouse(m_mouseState.lastPos);
    }

    if (event.type == sf::Event::MouseButtonReleased) {
        m_mouseState.isPressed = false;
    }

    
    if (event.type == sf::Event::MouseMoved) {
        if (m_mouseState.isPressed) {
            handleMouseEvent(event);
        }
        m_mouseState.lastPos = r_view.cellPosFromViewportPosition({event.mouseMove.x, event.mouseMove.y});
    }
}

void UI::handleMouseEvent(sf::Event& event) {
    Pos pos = r_view.cellPosFromViewportPosition({event.mouseMove.x, event.mouseMove.y});
    if (pos != m_mouseState.lastPos) {
       changeStateOfCellOnMouse(pos);
    }
}

void UI::changeStateOfCellOnMouse(Pos pos) {
    switch (m_mouseState.stateChanging) {
        case CellState::Normal:
            r_gridController.setStateOfCell(pos, CellState::Wall);
            break;
        case CellState::Wall:
            r_gridController.setStateOfCell(pos, CellState::Normal);
            break;
        case CellState::Goal:
            r_gridController.setStateOfCell(m_mouseState.lastPos, CellState::Normal);
            r_gridController.setStateOfCell(pos, CellState::Goal);
            r_gridController.resetSearch();
            break;
        case CellState::Start:
            r_gridController.setStateOfCell(m_mouseState.lastPos, CellState::Normal);
            r_gridController.setStateOfCell(pos, CellState::Start);
            r_gridController.resetSearch();
            break;
        default:
            break;
    }
}


void UI::drawUI(sf::RenderWindow& window) {
    m_text_count = 0;

    draw_backdrop_for_text(window);
    draw_text(window, "Space : Search");
    draw_text(window, "R : Reset Search");
    draw_text(window, "C : Clear Grid");

}

void UI::draw_text(sf::RenderWindow& window, const sf::String text) {
    sf::Text sf_text;
    sf_text.setFont(m_font);
    sf_text.setCharacterSize(26);
    sf_text.setFillColor(sf::Color::White);
    sf_text.setPosition(m_pos + m_margin + (sf::Vector2f){0, m_text_count * m_infoHeight}) ;
    sf_text.setString(text);
    window.draw(sf_text);
    m_text_count++;
}

void UI::draw_backdrop_for_text(sf::RenderWindow& window) {
    sf::RectangleShape backdrop;
    backdrop.setSize({300, 300});
    backdrop.setFillColor(sf::Color(0, 0, 0,150));
    backdrop.setPosition(m_pos + m_margin);
    window.draw(backdrop);
}


bool UI::load_font(const std::string& fontPath) {
    if (!m_font.loadFromFile(fontPath)) {
        std::cerr << "Failed to load font: " << fontPath << std::endl;
        return false;
    }
    return true;
}