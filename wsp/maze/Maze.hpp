#ifndef MAZE_MAZE_H
#define MAZE_MAZE_H

#include <stdio.h>
#include <vector>
#include <SFML/Graphics.hpp>
#include "MazeCell.hpp"

#endif //MAZE_MAZE_H

class Maze
{
public:
    Maze(int width, int height, int collumns, int rows, sf::RenderWindow* window);
    ~Maze();
    void Init();
    void Draw();
    MazeCell* GetRandomNeighbor(MazeCell* cell);
    void RemoveWalls(MazeCell* cell1, MazeCell* cell2);
    int GetMazeCellIndexByPosition(int x, int y);
    int generationStepSpeed = 10;
private:
    int width, height;
    int collumns, rows;
    bool completedGeneration = false;
    sf::RenderWindow* window;
    std::vector<MazeCell*> cells;
    std::vector<MazeCell*> stack;
    MazeCell* currentCell;
};


