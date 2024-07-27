#include "GridController.h" 

GridController::GridController(Grid& grid, BaseSearch& search) : r_grid(grid), r_search(search) {
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

                r_search.search();
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
    r_search.reset();
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