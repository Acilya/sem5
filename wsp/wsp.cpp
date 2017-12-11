//============================================================================
// Name        : wsp.cpp
// Author      : Alicja Kapiszka
// Version     :
// Description :
//============================================================================

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <iostream>
#include <thread>
#include <chrono>
#include <mutex>
#include <stdio.h>
#include <X11/Xlib.h>

const int SCREEN_WIDTH = 850;
const int SCREEN_HEIGHT = 850;

sf::RenderWindow *window = nullptr;
int maxLevel = 6;
std::mutex m;

void drawLine(std::pair<int,int> a, std::pair<int,int> b, sf::Color color)
{
    std::unique_lock<std::mutex> guard(m);
    sf::Vertex line[2] =
    {
		sf::Vertex(sf::Vector2f(a.first, a.second), color),
		sf::Vertex(sf::Vector2f(b.first, b.second), color)
    };
    window->draw(line, 2, sf::Lines);
    window->display();
}

void drawTriangle(std::pair<int,int> p1, std::pair<int,int> p2, std::pair<int,int> p3, int level)
{
	sf::Color color(rand() % 256, rand() % 256, rand() % 256);
	drawLine(p1, p2, color);
	std::this_thread::sleep_for(std::chrono::milliseconds(100));
	drawLine(p2, p3, color);
	std::this_thread::sleep_for(std::chrono::milliseconds(100));
	drawLine(p1, p3, color);
	std::this_thread::sleep_for(std::chrono::milliseconds(100));
	std::pair<int, int> p4, p5, p6;
	p4 = std::make_pair(p1.first, (p2.second - p1.second)/2 + p1.second);
	p5 = std::make_pair((p3.first - p2.first)/2 + p2.first, p2.second);
	p6 = std::make_pair(p5.first, p4.second);
	level = level + 1;
	if (level < maxLevel)
	{
		window->setActive(false);
		std::thread t1(drawTriangle, p1, p4, p6, level);
		std::thread t2(drawTriangle, p4, p2, p5, level);
		std::thread t3(drawTriangle, p6, p5, p3, level);
		t1.join();
		t2.join();
		t3.join();
	}
}

int main()
{
	XInitThreads();
	window = new sf::RenderWindow (sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Triangle");
	std::pair<int,int> p1, p2, p3;
	p1 = std::make_pair(20, 20);
	p2 = std::make_pair(20, 800);
	p3 = std::make_pair(800, 800);
	window->clear();
	drawTriangle(p1, p2, p3, 0);
	while (window->isOpen())
	{
		sf::Event event;
		while (window->pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window->close();
		}
	}
	return 0;
}
