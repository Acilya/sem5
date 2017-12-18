#ifndef MAZE_MAZECELL_H
#define MAZE_MAZECELL_H

#include <srdio.h>
#include <SFML/Graphics.hpp>

#endif //MAZE_MAZECELL_H

class MazeCell
{
public:
    MazeCell(int column, int row, int size, sf::RenderWindow* window);
    ~MazeCell();

    bool isVisited = false, inStack = false, isStart = false, isEnd = false;
    bool leftWall = true, rightWall = true, topWall = true, bottomWall = true;
    void Draw();
    int GetCollumn() { return collumn; }
    int GetRow() { return row; }
    void SetColor(sf::Color color);
private:
    int collumn, row;
    int size;
    int wallWidth = 2;
    sf::Color cellColor = sf::Color(0,0,0,255);
    sf::Color wallColor = sf::Color(0,0,0,255);
    sf::Color visitedColor = sf::Color(255,255,255,255);
    sf::Color inStackColor = sf::Color(255, 0, 0, 255);
    sf::Color endColor = sf::Color(0, 255, 0, 255);
    sf::Color startColor = sf::Color(255, 0, 0, 255);
    sf::RectangleShape cellShape;
    sf::RectangleShape leftWallShape, rightWallShape, topWallShape, bottomWallShape;
    sf::RenderWindow* window;
};


