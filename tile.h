#ifndef TILE_H
#define TILE_H

#include "constants.h"
#include <algorithm>

enum class Direction {LEFT, RIGHT, UP, DOWN};
class Tile
{
public:
    explicit Tile(int number, float x, float y);
    inline int number() const { return _number; }
    inline float x() const { return _x; }
    inline float y() const { return _y; }
    inline int row() const { return floor(_y) / (SlidePuzzle::CELL_SIZE+ SlidePuzzle::GAP); }
    inline int col() const { return floor(_x) / (SlidePuzzle::CELL_SIZE + SlidePuzzle::GAP); }
    void move(Direction dir, float vel);
    void setNumber(int number);

private:
    int _number;
    float _x, _y;
};

#endif // TILE_H
