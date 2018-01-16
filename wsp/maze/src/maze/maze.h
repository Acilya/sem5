#ifndef MAZE_H
#define MAZE_H

#include <vector>
#include <map>
#include "../cell/cell.h"

class Maze
{
public:
	
	Maze();
	~Maze();
	Maze(sf::RenderWindow * window, int totalColumns, int totalRows);
	Maze(const Maze & anotherMaze);
	Maze & operator=(Maze anotherMaze);

	void generate();
	void draw();

protected:

	bool hasBorderer(Cell & cell, Direction direction);
	Cell * getBorderer(Cell & cell, Direction direction);
	std::vector<std::pair<Direction, Cell *>> getBorderers(Cell & cell);
	void removeOppositeDirection(std::vector<std::pair<Direction, Cell *>> & borderers, Direction direction);
	void setWalls(Cell * currentCell, std::vector<std::pair<Direction, Cell *>> & borderers);
	friend void swap(Maze & leftMaze, Maze & rightMaze);

	int totalColumns;
	int totalRows;
	sf::RenderWindow * window;
	std::vector<std::vector<Cell>> board;
	bool isPositionInRange(float column, float row);
};

#endif
