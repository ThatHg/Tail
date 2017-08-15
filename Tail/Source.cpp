#include <SFML/Graphics.hpp>
#include "Level.h"
#include <stdexcept>
#include <iostream>

int main()
{
    Level level("level.lua");
    level.Initialize();

    sf::RenderWindow window(sf::VideoMode(720, 720), "SFML works!");
    try {
        while (window.isOpen()) {
            sf::Event event;
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed)
                    window.close();
            }

            window.clear(sf::Color(245, 245, 245, 255));

            level.Update(window);

            window.display();
        }
    }
    catch (const std::exception& ex) {
        std::cout << ex.what() << std::endl;
    }

    return 0;
}