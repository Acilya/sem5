#include "maze.h"

#ifndef COLORS_COLORS_H_
#define COLORS_COLORS_H_

class Colors : public Maze
{
public:
	Colors();
	Colors(sf::RenderWindow * window, int totalColumns, int totalRows);
	Colors(const Colors & anotherColors);
	virtual ~Colors();
	void Start();
	void Coloring(Cell * startingCell, sf::Color color);
};

#endif
