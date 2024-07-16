#include "App.h"

#include <SFML/Graphics.hpp>
#include <iostream>

#include "Grid.h"
#include "GridController.h"
#include "GridView.h"
#include "UI.h"

void App::Run() {
    sf::RenderWindow window(sf::VideoMode(1200, 900), "Pathfinder", sf::Style::Close | sf::Style::Titlebar);

    Grid grid = Grid({20, 15});
    
    GridController grid_controller = GridController(grid);
    UI ui = UI(grid_controller, {900, 0});
    GridView view = GridView(grid, {900, 900});


    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) window.close();

            grid_controller.handleEvent(event);
        }

        window.clear(sf::Color(50, 50, 50));

        view.draw_grid(window);
        ui.drawUI(window);
        window.display();
    }

    return;
}