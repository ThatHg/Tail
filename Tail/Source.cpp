#include <SFML/Graphics.hpp>
#include "Level.h"

int main()
{
    Level level("level.lua");
    level.Initialize();

    sf::RenderWindow window(sf::VideoMode(1280, 720), "SFML works!");

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear(sf::Color(100,50,50,255));

        level.Update(window);

        window.display();
    }

    return 0;
}