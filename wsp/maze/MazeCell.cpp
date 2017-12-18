#include "MazeCell.hpp"

MazeCell::MazeCell(int column, int row, int size, sf::RenderWindow* window) : collumn(collumn), row(row), size(size),
                                                                              window(window)

{
    sf::Vector2f cellPosition = sf::Vector2f(size * collumn, size * row);
    //Cell
    cellShape = sf::RectangleShape(sf::Vector2f(size, size));
    cellShape.setPosition(cellPosition.x, cellPosition.y);
    cellShape.setFillColor(sf::Color(rand() % 255, rand() % 255, rand() % 255, 255));
    //Walls
    leftWallShape = sf::RectangleShape(sf::Vector2f(wallWidth, size));
    leftWallShape.setPosition(cellPosition.x, cellPosition.y);
    leftWallShape.setFillColor(wallColor);
    rightWallShape = sf::RectangleShape(sf::Vector2f(wallWidth, size));
    rightWallShape.setPosition(cellPosition.x + size - wallWidth, cellPosition.y);
    rightWallShape.setFillColor(wallColor);
    topWallShape = sf::RectangleShape(sf::Vector2f(size, wallWidth));
    topWallShape.setPosition(cellPosition.x, cellPosition.y);
    topWallShape.setFillColor(wallColor);
    topWallShape = sf::RectangleShape(sf::Vector2f(size, wallWidth));
    topWallShape.setPosition(cellPosition.x, cellPosition.y + size - wallWidth);
    topWallShape.setFillColor(wallColor);
}
MazeCell::~MazeCell()
{

}

void MazeCell::SetColor(sf::Color color)
{
    if(cellShape.getFillColor() != color)
    {
        cellShape.setFillColor(color);
    }
}

void MazeCell::Draw()
{
    if(inStack)
    {
        SetColor(inStackColor);
    }
    else if(isVisited && isEnd)
    {
        SetColor(endColor);
    }
    else if(isVisited && isStart)
    {
        SetColor(startColor);
    }
    else if(isVisited)
    {
        SetColor(visitedColor);
    }
    window->draw(cellShape);
    if(leftWall)
    {
        window->draw(leftWallShape);
    }
    if(rightWall)
    {
        window->draw(rightWallShape);
    }
    if(topWall)
    {
        window->draw(topWallShape);
    }
    if(bottomWall)
    {
        window->draw(bottomWallShape);
    }
}
