#include <iostream>
#include <stack>
#include "maze.h"

#include <chrono>
#include <thread>


Maze::Maze()
	: window(nullptr), totalColumns(0), totalRows(0)
{
}


Maze::~Maze()
{
}


Maze::Maze(sf::RenderWindow * window, int totalColumns, int totalRows)
	: window(window), totalColumns(totalColumns), totalRows(totalRows)
{
	for(int i = 0; i < totalColumns; ++i)
	{
		board.push_back(std::vector<Cell>());
		for(int j = 0; j < totalRows; ++j)
		{
			board[i].push_back(Cell(i, j));
		}
	}

	for(int i = 0; i < totalColumns; ++i)
	{
		for(int j = 0; j < totalRows; ++j)
		{
			if(0 == i)
			{
				board[i][j].setWallPresence(Direction::LEFT, true);
			}

			if(totalColumns - 1 == i)
			{
				board[i][j].setWallPresence(Direction::RIGHT, true);
			}

			if(0 == j)
			{
				board[i][j].setWallPresence(Direction::UP, true);
			}

			if(totalRows - 1 == j)
			{
				board[i][j].setWallPresence(Direction::DOWN, true);
			}
		}
	}
}


Maze::Maze(const Maze & anotherMaze)
	: Maze(anotherMaze.window, anotherMaze.totalColumns, anotherMaze.totalRows)
{
	for(int i = 0; i < totalColumns; ++i)
	{
		for(int j = 0; j < totalRows; ++j)
		{
			board[i][j] = anotherMaze.board[i][j];
		}
	}	
}


Maze & Maze::operator=(Maze anotherMaze)
{
	swap(*this, anotherMaze);
	return *this;
}


void Maze::generate()
{
	std::stack<Cell*> cellStack;

	// Start generate from first Cell
	cellStack.push(&board[0][0]);
	Direction lastDirection = Direction::LAST_ITEM;

	while(!cellStack.empty())
	{
		Cell * currentCell = cellStack.top();
		if(CellState::COMPLETE != currentCell->getCellState())
		{
			currentCell->setCellState(CellState::VISITED);
		}

		//Get borderers
		std::vector<std::pair<Direction, Cell *>> borderers = getBorderers(*currentCell);
		removeOppositeDirection(borderers,lastDirection);
		//Shuffle borderers
		std::random_shuffle(borderers.begin(), borderers.end());
		//check if complete
		bool canMove = false;
		for (auto borderer : borderers)
		{
			if(CellState::NON_VISITED ==  borderer.second->getCellState())
			{
				canMove = true;
				break;
			}
		}
		if(!canMove && CellState::NON_VISITED != currentCell->getCellState())
		{
			currentCell->setCellState(CellState::COMPLETE);
			cellStack.pop();
			continue;
		}

		//Set walls
		setWalls(currentCell, borderers);

		bool move = false;
		for(int iter = 0; iter < borderers.size(); ++iter)
		{
			Direction newDirection = borderers[iter].first;
			Cell * cell = borderers[iter].second;

			switch(cell->getCellState())
			{
				case CellState::NON_VISITED:
					if(!move)
					{
						lastDirection = newDirection;
						cellStack.push(cell);
						move = true;
					}
					break;
			}
		}
		if(!move)
		{
			lastDirection = Direction::LAST_ITEM;
		}
		/*std::this_thread::sleep_for(std::chrono::milliseconds(200));
		window->clear();
		draw();
		window->display();*/
	}
}


void Maze::draw()
{
	board[0][0].draw(window);
	for(int i = 0; i < totalColumns; ++i)
	{
		for(int j = 0; j < totalRows; ++j)
		{
			board[i][j].draw(window);
		}
	}
}


bool Maze::isPositionInRange(float column, float row)
{
	return !(0 > column || 0 > row || totalColumns <= column || totalRows <= row);
}


bool Maze::hasBorderer(Cell& cell, Direction direction)
{
	bool result = false;

	switch(direction)
	{
		case Direction::UP:
			result = isPositionInRange(cell.getColumn(), cell.getRow() - 1);
			break;
		case Direction::DOWN:
			result = isPositionInRange(cell.getColumn(), cell.getRow() + 1);
			break;
		case Direction::LEFT:
			result = isPositionInRange(cell.getColumn() - 1, cell.getRow());
			break;
		case Direction::RIGHT:
			result = isPositionInRange(cell.getColumn() + 1, cell.getRow());
			break;
	}

	return result;
}


Cell * Maze::getBorderer(Cell & cell, Direction direction)
{
	Cell * resultCell = nullptr;
	switch(direction)
	{
		case Direction::UP:
			resultCell = &board[cell.getColumn()][cell.getRow() - 1];
			break;
		case Direction::DOWN:
			resultCell = &board[cell.getColumn()][cell.getRow() + 1];
			break;
		case Direction::LEFT:
			resultCell = &board[cell.getColumn() - 1][cell.getRow()];
			break;
		case Direction::RIGHT:
			resultCell = &board[cell.getColumn() + 1][cell.getRow()];
			break;
	}
	return resultCell;
}


std::vector<std::pair<Direction, Cell *>> Maze::getBorderers(Cell & cell)
{
	std::vector<std::pair<Direction, Cell *>> borderers;

	if(hasBorderer(cell, Direction::UP))
	{
		borderers.push_back(std::make_pair(Direction::UP, getBorderer(cell, Direction::UP)));
	}
	if(hasBorderer(cell, Direction::DOWN))
	{
		borderers.push_back(std::make_pair(Direction::DOWN, getBorderer(cell, Direction::DOWN)));
	}
	if(hasBorderer(cell, Direction::LEFT))
	{
		borderers.push_back(std::make_pair(Direction::LEFT, getBorderer(cell, Direction::LEFT)));
	}
	if(hasBorderer(cell, Direction::RIGHT))
	{
		borderers.push_back(std::make_pair(Direction::RIGHT, getBorderer(cell, Direction::RIGHT)));
	}

	return borderers;
}



void Maze::removeOppositeDirection(std::vector<std::pair<Direction, Cell *>> & borderers, Direction direction)
{
	Direction oppositeDirection;
	switch(direction)
	{
		case Direction::UP:
			oppositeDirection = Direction::DOWN;
			break;
		case Direction::DOWN:
			oppositeDirection = Direction::UP;
			break;
		case Direction::LEFT:
			oppositeDirection = Direction::RIGHT;
			break;
		case Direction::RIGHT:
			oppositeDirection = Direction::LEFT;
			break;
	}

	int iter = 0;
	for(; iter < borderers.size(); ++iter)
	{
		if(borderers[iter].first == oppositeDirection)
		{
			break;
		}
	}
	borderers.erase(borderers.begin() + iter);
}


void Maze::setWalls(Cell * currentCell, std::vector<std::pair<Direction, Cell *>> & borderers)
{
	for(auto borderer : borderers)
	{
		Direction newDirection = borderer.first;
		Cell * cell = borderer.second;

		switch(cell->getCellState())
		{

			case CellState::VISITED:
				cell->setWallPresenceOpposite(newDirection, true);
				currentCell->setWallPresence(newDirection, true);
				break;
		}
	}	
}


void swap(Maze & leftMaze, Maze & rightMaze)
{
	std::swap(leftMaze.totalColumns, rightMaze.totalColumns);
	std::swap(leftMaze.totalRows, rightMaze.totalRows);
	std::swap(leftMaze.board, rightMaze.board);
}
