#include <ctime>
#include <cstdlib>

#include <SFML/Graphics.hpp>
#include "maze/maze.h"
#include "maze/Colors.h"

int main(int argc, char** argv)
{
    srand(time(0));

    sf::RenderWindow window(sf::VideoMode(750, 750), "Maze", sf::Style::Close);

    Colors maze(&window, 50, 50);
    maze.generate();

    while(window.isOpen())
    {
        sf::Event event;

        while(window.pollEvent(event))
        {
            switch(event.type)
            {
                case sf::Event::Closed:
                    window.close();
                    break;
            }
        }

        window.clear();

        maze.draw();
        maze.Start();

        window.display();
    }
}
