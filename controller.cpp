#include "controller.h"
#include "model.h"

Controller::Controller(Model *pModel):
    _pModel(pModel)
{}

void Controller::newGame()
{
    _pModel->newGame();
}

void Controller::tryToSlide(int cursorX, int cursorY)
{
    if(!_pModel->isWin())
    {
        int row = cursorY / (SlidePuzzle::CELL_SIZE + SlidePuzzle::GAP);
        int col = cursorX / (SlidePuzzle::CELL_SIZE + SlidePuzzle::GAP);
        if(row >= 0 && row < _pModel->boardSizeX() &&
           col >= 0 && col < _pModel->boardSizeY())
        {
            _pModel->tryToSlide(row, col);
        }
    }
}
