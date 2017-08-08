#ifndef CONSTANTMODELINTERFACE_H
#define CONSTANTMODELINTERFACE_H
#include "tile.h"

class ConstantModelInterface
{
public:
    virtual bool isWin() const = 0;
    virtual int boardSizeX() const  = 0;
    virtual int boardSizeY() const = 0;
    virtual int getNumSlides() const = 0;
    virtual int getTileNumber(int row, int col) const = 0;
    virtual const Tile* getTileByIndex(int index) const = 0;
};

#endif // CONSTANTMODELINTERFACE_H
