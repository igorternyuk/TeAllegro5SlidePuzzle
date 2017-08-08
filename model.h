#ifndef MODEL_H
#define MODEL_H

#include <vector>
#include <list>
#include "constantmodelinterface.h"
#include <modellistener.h>
#include "tile.h"

class Model : public ConstantModelInterface
{
public:
    explicit Model(int numRows = 4, int numCols = 4);
    ~Model();
    //////Constant model interface/////////////
    virtual inline bool isWin() const { return _isWin; }
    virtual inline int boardSizeX() const { return _boardSizeX; }
    virtual inline int boardSizeY() const { return _boardSizeY; }
    virtual inline int getNumSlides() const { return _numSlides; }
    virtual inline const Tile* getTileByIndex(int index) const { return _tiles.at(index); }
    virtual int getTileNumber(int row, int col) const;
    ////////////////////////////////////////////
    bool tryToSlide(int row, int col);
    void newGame();
    void addListener(ModelListener* listener);
    void removeListener(ModelListener *listener);

private:
    int _boardSizeX, _boardSizeY;
    std::vector<Tile*> _tiles;
    std::list<ModelListener*> _listeners;
    int _numSlides {0};
    bool _isWin {false};
    bool _isMoving {false};
    int _emptyRow, _emptyCol;

    void generateRandomSetup();
    bool alreadyContains(int num);
    bool isPossibleToResolve();
    void makeResolutionPossible();
    //void slide(Tile &tile, Direction dir);
    void checkWin();
    void notifyAllListeners();
    void clearTiles();
#ifdef DEBUG
    void printField();
#endif
};

#endif // MODEL_H
