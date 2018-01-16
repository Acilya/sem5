#ifndef CELL_H
#define CELL_H

#include <SFML/Graphics.hpp>


enum class Direction
{
	UP,
	DOWN,
	LEFT,
	RIGHT,
	LAST_ITEM
};

enum class CellState
{
	NON_VISITED,
	VISITED,
	COMPLETE
};

class Cell
{
public:

	Cell();
	Cell(float column, float row);
	float getColumn();
	float getRow();
	CellState getCellState();
	void setCellState(CellState state);
	void setWallPresence(Direction direction, bool presence);
	bool getWallPresence(Direction direction);
	void setWallPresenceOpposite(Direction direction, bool presence);
	void draw(sf::RenderWindow * window);
	static sf::RectangleShape getRectangle();

protected:
	void drawWalls(sf::RenderWindow * window, sf::Vector2f hookPosition);
	void drawLine(sf::RenderWindow * window, sf::Vector2f start, sf::Vector2f end);
	bool upWall;
	bool downWall;
	bool leftWall;
	bool rightWall;
	float column;
	float row;
	CellState state;

	// TODO: separate GUI from business logic
	static sf::Color NON_VISITED_COLOR;
	static sf::Color VISITED_COLOR;
	static sf::Color COMPLETE_COLOR;
	static sf::RectangleShape rectangle;
	static float rectangleWidth;
	static float rectangleHeight;
};

#endif
