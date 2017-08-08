#include "tile.h"
#include <algorithm>

Tile::Tile(int number, float x, float y):
    _number(number), _x(x), _y(y)
{}

void Tile::move(Direction dir, float vel)
{
    switch(dir)
    {
        case Direction::UP:
            _y -= vel;
        break;
        case Direction::DOWN:
            _y += vel;
        break;
        case Direction::LEFT:
            _x -= vel;
        break;
        case Direction::RIGHT:
            _x += vel;
        break;
    }
}

void Tile::setNumber(int number)
{
    _number = number;
}

