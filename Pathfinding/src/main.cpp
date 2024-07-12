#include <SFML/Graphics.hpp>
#include <iostream>
#include "Grid.h"
#include "UI.h"

int main()
{
    sf::RenderWindow window(sf::VideoMode(1600, 1200), "SFML works!");
    std::cout << "Pathfinding" << std::endl;

    sf::Font font;
    font.loadFromFile("Raleway-Regular.ttf");
  
    Grid grid(false);
    grid.set_font(font);
    UI ui(&window, font, &grid);


    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::KeyPressed) {
                switch (event.key.code)
                {
                case(sf::Keyboard::R):
                    grid.reset();
                    break;

                case(sf::Keyboard::C):
                    grid.clear();
                    break;
                case(sf::Keyboard::Space):
                    grid.pause();
                    break;
                case(sf::Keyboard::T):
                    grid.try_again();
                    break;
                case(sf::Keyboard::D):
                    grid.diagonal();
                    break;

                case(sf::Keyboard::L):
                    grid.make_ex4();
                    break;

                case(sf::Keyboard::A):
                    grid.search();
                default:
                    break;
                }
            }
                

        }

        window.clear(sf::Color(50,50,50));
        
        if (!grid.m_done)
        {
            // grid.search();
        }

        ui.drawUI();
        grid.draw_grid(&window);


        window.display();
    }

    return 0;
}