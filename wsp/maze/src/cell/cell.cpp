#include <iostream>
#include <ctime>
#include <cstdlib>
#include "cell.h"

sf::Color Cell::NON_VISITED_COLOR = sf::Color::Black;
sf::Color Cell::VISITED_COLOR = sf::Color::Red;
sf::Color Cell::COMPLETE_COLOR = sf::Color::White;
float Cell::rectangleWidth = 15.0f;
float Cell::rectangleHeight = 15.0f;
sf::RectangleShape Cell::rectangle = sf::RectangleShape(
										sf::Vector2f(Cell::rectangleWidth, Cell::rectangleHeight));

Cell::Cell()
	: upWall(false), downWall(false), leftWall(false), rightWall(false),
	column(0.0f), row(0.0f), state(CellState::NON_VISITED)
{
}


Cell::Cell(float column, float row)
	: Cell()
{
	this->column = column;
	this->row = row;
}


float Cell::getColumn()
{
	return this->column;
}


float Cell::getRow()
{
	return this->row;
}


CellState Cell::getCellState()
{
	return this->state;
}


void Cell::setCellState(CellState state)
{
	this->state = state;
}



bool Cell::getWallPresence(Direction direction)
{
	bool resultWallPresence = false;
	switch(direction)
		{
			case Direction::UP:
				resultWallPresence = upWall;
				break;

			case Direction::DOWN:
				resultWallPresence = downWall;
				break;

			case Direction::LEFT:
				resultWallPresence = leftWall;
				break;

			case Direction::RIGHT:
				resultWallPresence = rightWall;
				break;

			default:
				// TODO
				break;
		}

	return resultWallPresence;
}


void Cell::setWallPresence(Direction direction, bool presence)
{
	switch(direction)
	{
		case Direction::UP:
			upWall = presence;
			break;

		case Direction::DOWN:
			downWall = presence;
			break;

		case Direction::LEFT:
			leftWall = presence;
			break;

		case Direction::RIGHT:
			rightWall = presence;
			break;

		default:
			// TODO
			break;
	}
}


void Cell::setWallPresenceOpposite(Direction direction, bool presence)
{
	switch(direction)
	{
		case Direction::UP:
			downWall = presence;
			break;

		case Direction::DOWN:
			upWall = presence;
			break;

		case Direction::LEFT:
			rightWall = presence;
			break;

		case Direction::RIGHT:
			leftWall = presence;
			break;

		default:
			// TODO
			break;
	}
}

void Cell::draw(sf::RenderWindow * window)
{
	sf::Vector2f hookPosition(
			column * Cell::rectangleWidth,
			row * Cell::rectangleHeight);
	Cell::rectangle.setPosition(hookPosition);

	switch(state)
	{
		case CellState::NON_VISITED:
			Cell::rectangle.setFillColor(Cell::NON_VISITED_COLOR);
			break;

		case CellState::VISITED:
			Cell::rectangle.setFillColor(Cell::VISITED_COLOR);
			break;

		case CellState::COMPLETE:
			Cell::rectangle.setFillColor(Cell::COMPLETE_COLOR);
			break;
	}

	window->draw(Cell::rectangle);
	drawWalls(window, hookPosition);
}


void Cell::drawWalls(sf::RenderWindow * window, sf::Vector2f hookPosition)
{
	sf::Vector2f end;
	
	if(upWall)
	{
		end = hookPosition +  sf::Vector2f(Cell::rectangleWidth, 0);
		drawLine(window, hookPosition, end);
	}

	if(downWall)
	{
		end = hookPosition +  sf::Vector2f(Cell::rectangleWidth, Cell::rectangleHeight);
		drawLine(window, 
			hookPosition + sf::Vector2f(0, Cell::rectangleHeight), 
			end);
	}

	if(leftWall)
	{
		end = hookPosition + sf::Vector2f(0, Cell::rectangleHeight);
		drawLine(window, hookPosition, end);
	}


	if(rightWall)
	{
		end = hookPosition + sf::Vector2f(Cell::rectangleWidth, Cell::rectangleHeight);
		drawLine(window, 
			hookPosition + sf::Vector2f(Cell::rectangleWidth, 0), 
			end);
	}
}


void Cell::drawLine(sf::RenderWindow * window, sf::Vector2f start, sf::Vector2f end)
{
	sf::VertexArray line(sf::LinesStrip, 2);
 	line[0].position = start;
 	line[1].position = end;
 	line[0].color = sf::Color::Black;
 	line[1].color = sf::Color::Black;

 	window->draw(line);
}

sf::RectangleShape Cell::getRectangle()
{
	return Cell::rectangle;
}
