#include "GridController.h" 
#include "Grid.h"

GridController::GridController(Grid& grid) : m_grid(grid) {
    m_paused = true;
    m_done = false;
    m_win = false;
    reset();
}

void GridController::handleEvent(sf::Event& event) {
    if (event.type == sf::Event::KeyPressed) {
        switch (event.key.code) {
            case (sf::Keyboard::R):
                reset();
                break;
            case (sf::Keyboard::C):
                clear();
                break;
            case (sf::Keyboard::Space):
                pause();
                break;
            case (sf::Keyboard::T):
                try_again();
                break;
            case (sf::Keyboard::D):
                diagonal();
                break;
            default:
                break;
        }
    }
}



void GridController::reset() {
    srand(time(NULL));

    return;
}

void GridController::clear() {
    reset();
}

void GridController::pause() {
    m_paused = !m_paused;
}

void GridController::try_again() {


  return;
}

void GridController::diagonal() {
    return;

}