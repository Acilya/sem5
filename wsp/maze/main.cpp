//https://www.youtube.com/watch?v=xrFFubkyZWM

#include <stdio.h>
#include <SFML/Graphics.hpp>
#include "Maze.hpp"

int main(int argc, char** argv)
{
    sf::RenderWindow window(sf::VideoMode(1600,1600), "Maze", sf::Style::Close);
    Maze maze(1600, 1600, 40, 40, &window);
    while(window.isOpen())
    {
        sf::Event evnt;
        while(window.pollEvent(evnt))
        switch(evnt.type)
        {
            case sf::Event::Closed:
                window.close();
                break;
        }
        window.clear();
        window.display();
    }
}