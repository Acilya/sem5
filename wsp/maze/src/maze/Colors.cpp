#include "Colors.h"
#include <thread>
#include <iostream>

Colors::Colors() : Maze()
{

}

Colors::~Colors()
{

}

Colors::Colors(sf::RenderWindow * window, int totalColumns, int totalRows) : Maze(window, totalColumns, totalRows)
{

}
Colors::Colors(const Colors & anotherColors) : Maze(anotherColors)
{

}

void Colors::Coloring(Cell * startingCell, sf::Color color)
{
	sf::RectangleShape rect = Cell::getRectangle();
	rect.setFillColor(color);
	window->draw(rect);

	int freeWays = startingCell->getWallPresence(Direction::UP) + startingCell->getWallPresence(Direction::DOWN) +
			startingCell->getWallPresence(Direction::RIGHT) + startingCell->getWallPresence(Direction::LEFT);

	Cell * nextCell = nullptr;
	if(startingCell->getWallPresence(Direction::RIGHT))
	{
		nextCell = &board[startingCell->getRow()][startingCell->getColumn()+1];
		Colors::Coloring(nextCell, color);
		if(freeWays > 1)
		{
			if(startingCell->getWallPresence(Direction::DOWN))
			{
				nextCell = &board[startingCell->getRow()+1][startingCell->getColumn()];
				std::thread t(&Colors::Coloring, this, nextCell, sf::Color(rand() % 256, rand() % 256, rand() % 256));
				t.join();
			}
			if(startingCell->getWallPresence(Direction::UP))
			{
				nextCell = &board[startingCell->getRow()-1][startingCell->getColumn()+1];
				std::thread t(&Colors::Coloring, this, nextCell, sf::Color(rand() % 256, rand() % 256, rand() % 256));
				t.join();
			}
			if(startingCell->getWallPresence(Direction::LEFT))
			{
				nextCell = &board[startingCell->getRow()][startingCell->getColumn()-1];
				std::thread t(&Colors::Coloring, this, nextCell, sf::Color(rand() % 256, rand() % 256, rand() % 256));
				t.join();
			}
		}
	}
	else if(startingCell->getWallPresence(Direction::DOWN))
	{
		nextCell = &board[startingCell->getRow()+1][startingCell->getColumn()];
		Colors::Coloring(nextCell, color);
		if(freeWays > 1)
		{
			if(startingCell->getWallPresence(Direction::UP))
			{
				nextCell = &board[startingCell->getRow()-1][startingCell->getColumn()+1];
				std::thread t(&Colors::Coloring, this, nextCell, sf::Color(rand() % 256, rand() % 256, rand() % 256));
				t.join();
			}
			if(startingCell->getWallPresence(Direction::LEFT))
			{
				nextCell = &board[startingCell->getRow()][startingCell->getColumn()-1];
				std::thread t(&Colors::Coloring, this, nextCell, sf::Color(rand() % 256, rand() % 256, rand() % 256));
				t.join();
			}
		}
	}
	else if(startingCell->getWallPresence(Direction::UP))
	{
		nextCell = &board[startingCell->getRow()-1][startingCell->getColumn()+1];
		Colors::Coloring(nextCell, color);
		if(freeWays > 1 && startingCell->getWallPresence(Direction::LEFT))
		{
			nextCell = &board[startingCell->getRow()][startingCell->getColumn()-1];
			std::thread t(&Colors::Coloring, this, nextCell, sf::Color(rand() % 256, rand() % 256, rand() % 256));
			t.join();
		}
	}
	else if(startingCell->getWallPresence(Direction::LEFT))
	{
		nextCell = &board[startingCell->getRow()][startingCell->getColumn()-1];
		Colors::Coloring(nextCell, color);
	}
}

void Colors::Start()
{
	std::thread t1(&Colors::Coloring, this, &board[0][0], sf::Color::Red);
	t1.join();
}

