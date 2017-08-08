#include "model.h"
#include <algorithm>
#include <cmath>
#include <ctime>
#include <iostream>

Model::Model(int numRows, int numCols):
    _boardSizeX(numRows), _boardSizeY(numCols)
{
    generateRandomSetup();
    if(!isPossibleToResolve())
        makeResolutionPossible();
}

Model::~Model()
{
    clearTiles();
}

bool Model::tryToSlide(int row, int col)
{
    int indexOfClickedTile = -1;
    for(int i{0}; i < int(_tiles.size()); ++i)
    {
        if(_tiles.at(i)->row() == row && _tiles.at(i)->col() == col)
        {
            indexOfClickedTile = i;
            break;
        }
    }
    if(indexOfClickedTile == -1) return false;
    //Empty square is on the left side
    if(row == _emptyRow && col == _emptyCol + 1)
    {
        _tiles[indexOfClickedTile]->move(Direction::LEFT, SlidePuzzle::CELL_SIZE + SlidePuzzle::GAP);
        _emptyCol = col;
    }
    //Empty square is on the right side
    else if(row == _emptyRow && col == _emptyCol - 1)
    {
        _tiles[indexOfClickedTile]->move(Direction::RIGHT, SlidePuzzle::CELL_SIZE + SlidePuzzle::GAP);
        _emptyCol = col;
    }
    //Empty square is on the top
    else if(col == _emptyCol && row == _emptyRow + 1)
    {
        _tiles[indexOfClickedTile]->move(Direction::UP, SlidePuzzle::CELL_SIZE + SlidePuzzle::GAP);
        _emptyRow = row;
    }
    //Empty square is on the bottom
    else if(col == _emptyCol && row == _emptyRow - 1)
    {
        _tiles[indexOfClickedTile]->move(Direction::DOWN, SlidePuzzle::CELL_SIZE + SlidePuzzle::GAP);
        _emptyRow = row;
    }
    ++_numSlides;
    checkWin();
#ifdef DEBUG
    printField();
#endif
    notifyAllListeners();
    return true;
}

void Model::newGame()
{
    _numSlides  = 0;
    _isWin = false;
    _isMoving = false;
    generateRandomSetup();
    if(!isPossibleToResolve())
        makeResolutionPossible();
}

void Model::addListener(ModelListener *listener)
{
    _listeners.push_back(listener);
}

void Model::removeListener(ModelListener *listener)
{
    _listeners.remove(listener);
}

int Model::getTileNumber(int row, int col) const
{
    auto it = std::find_if(_tiles.begin(), _tiles.end(), [&](auto tile){
        return tile->row() == row && tile->col() == col;
    });
    return (*it)->number();
}

void Model::generateRandomSetup()
{
    clearTiles();
    srand(time(0));
    for(int i{0}; i < _boardSizeY; ++i)
    {
        for(int j{0}; j < (i == _boardSizeY - 1 ? _boardSizeX - 1: _boardSizeX); ++j)
        {
            int rnd;
            do
            {
                rnd = rand() % (_boardSizeX * _boardSizeY - 1) + 1;
            }
            while(alreadyContains(rnd));
            int tx = j * (SlidePuzzle::CELL_SIZE + SlidePuzzle::GAP);
            int ty = i * (SlidePuzzle::CELL_SIZE + SlidePuzzle::GAP);
            Tile *pTile = new Tile(rnd, tx, ty);
            _tiles.push_back(pTile);
        }
    }
    _emptyRow = _boardSizeY - 1;
    _emptyCol = _boardSizeX - 1;
}

bool Model::alreadyContains(int num)
{
    bool result = false;
    for(auto t: _tiles)
    {
        if(t->number() == num)
        {
            result = true;
            break;
        }
    }
    return result;
}

bool Model::isPossibleToResolve()
{
    int numChaos {0};
    for(int i{0}; i < int(_tiles.size()); ++i)
    {
        for(int j{0}; j < i; ++j)
        {
            if(_tiles.at(j)->number() > _tiles.at(i)->number())
                ++numChaos;
        }
    }
    return numChaos % 2 == 0;
}

void Model::makeResolutionPossible()
{
#ifdef DEBUG
    printField();
    std::cout << "Setup is not solvable" << std::endl;
#endif
    int buf = _tiles[_tiles.size() - 1]->number();
    _tiles[_tiles.size() - 1]->setNumber(_tiles[_tiles.size() - 2]->number());
    _tiles[_tiles.size() - 2]->setNumber(buf);
    notifyAllListeners();
#ifdef DEBUG
    printField();
#endif
}

/*void Model::slide(Tile &tile, Direction dir)
{
    float frameTime = 0.f, deltaTime = 0;
    float distance = SlidePuzzle::CELL_SIZE + SlidePuzzle::GAP;
    int countSteps = 0;
    const int numSteps = 100;
    float animDelay = 10.0f;
    clock_t prev = std::clock();
    clock_t curr = std::clock();
    std::cout << "tile.x = " << tile.x() << " tile.y = " << tile.y() << std::endl;
    while(countSteps < numSteps)
    {
        prev = curr;
        curr = std::clock();
        //For faster computers frameTime will increase slowly
        //because time diference deltaTime is less
        deltaTime = (curr - prev) / 1000.0f;
        std::cout << "delta_t = " << deltaTime << std::endl;
        frameTime += deltaTime;
        std::cout << "frame_time = " << frameTime << std::endl;
        ++frameTime;
        std::cout << "frame_time = " << frameTime << std::endl;
        if(frameTime > animDelay)
        {
            tile.move(dir, SlidePuzzle::CELL_SIZE + SlidePuzzle::GAP);
            ++countSteps;
            notifyAllListeners(); //Send update signal
            frameTime = 0.f;
            std::cout << "tile.x = " << tile.x() << " tile.y = " << tile.y() << std::endl;
        }

    }
}*/

void Model::checkWin()
{
    for(auto tile: _tiles)
    {
        int number = tile->number();
        if(tile->row() != (number - 1) / _boardSizeY ||
           tile->col() != (number - 1) % _boardSizeX)
        {
            _isWin = false;
            return;
        }
    }
    _isWin = true;
}

void Model::notifyAllListeners()
{
    for(auto &l: _listeners)
        l->updateView();
}

void Model::clearTiles()
{
    for(auto &tile: _tiles)
        delete tile;
    _tiles.clear();
}

#ifdef DEBUG
void Model::printField()
{
    int k = 0;
    for(auto it = _tiles.begin(); it != _tiles.end(); ++it)
    {
        std::cout << (*it)->number() << " ";
        if(++k % 4 == 0)
        {
            std::cout << std::endl;
        }
    }
    std::cout << std::endl;
    std::cout << "--------------------------" << std::endl;
}
#endif
