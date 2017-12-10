//============================================================================
// Name        : wsp.cpp
// Author      : Alicja Kapiszka
// Version     :
// Description :
//============================================================================

#include <SFML/Graphics.hpp>
#include <iostream>
#include <thread>
#include <stdio.h>

const int SCREEN_WIDTH = 1050;
const int SCREEN_HEIGHT = 850;

sf::RenderWindow *window = nullptr;
int maxLevel = 3;
bool end = false;

void drawTriangle(std::pair<int,int> p1, std::pair<int,int> p2, std::pair<int,int> p3, int level)
{
	sf::Color color(rand() % 256, rand() % 256, rand() % 256);
	sf::Vertex line1[2] =
	{
		sf::Vertex(sf::Vector2f(p1.first, p1.second), color),
		sf::Vertex(sf::Vector2f(p2.first, p2.second), color)
	};
	sf::Vertex line2[2] =
	{
		sf::Vertex(sf::Vector2f(p1.first, p1.second), color),
		sf::Vertex(sf::Vector2f(p3.first, p3.second), color)
	};
	sf::Vertex line3[2] =
	{
		sf::Vertex(sf::Vector2f(p3.first, p3.second), color),
		sf::Vertex(sf::Vector2f(p2.first, p2.second), color)
	};
	window->draw(line1, 2, sf::Lines);
	window->draw(line2, 2, sf::Lines);
	window->draw(line3, 2, sf::Lines);
	//window->display();
	std::pair<int, int> p4, p5, p6;
	p4 = std::make_pair(p1.first, (p2.second - p1.second)/2);
	p5 = std::make_pair((p3.first - p2.first)/2, p2.second);
	p6 = std::make_pair(p5.first, p4.second);
	int new_level = level + 1;
	if (new_level < maxLevel)
	{
		std::cout << p4.first << " " << p4.second << " " << p5.first << " " << p5.second << " " << p6.first << " " << p6.second << std::endl;
		window->setActive(false);
		std::thread t1(drawTriangle, p1, p4, p6, new_level);
		std::thread t2(drawTriangle, p4, p2, p5, new_level);
		std::thread t3(drawTriangle, p6, p5, p3, new_level);
		t1.join();
		t2.join();
		t3.join();
	}
	else
		end = true;
}

int main()
{
	window = new sf::RenderWindow (sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Triangle");
	std::pair<int,int> p1, p2, p3;
	p1 = std::make_pair(20, 20);
	p2 = std::make_pair(20, 800);
	p3 = std::make_pair(1024, 800);

	window->clear();
	while (window->isOpen())
	{
		sf::Event event;
		while (window->pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window->close();
		}
		if (!end)
		{
			drawTriangle(p1, p2, p3, 0);
			window->display();
		}
	}
	return 0;
}
