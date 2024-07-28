#include "App.h"

#include <SFML/Graphics.hpp>
#include <iostream>

#include "Grid.h"
#include "GridController.h"
#include "GridView.h"
#include "UI.h"
#include "Search.h"

void App::Run() {
    sf::RenderWindow window(sf::VideoMode(1200, 900), "Pathfinder", sf::Style::Close );

    Grid grid = Grid({40, 30});
    
    AstarSearch search(grid);   
    GridController grid_controller(grid, search);
    GridView view(grid, search, {1200, 900});
    UI ui(grid_controller, view, {900, 0});


    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) window.close();

            ui.handleEvent(event);
        }

        window.clear(sf::Color(50, 50, 50));
        view.draw_grid(window);
        view.draw_search(window);

        ui.drawUI(window);

        window.display();
    }

    return;
}