#ifndef CONTROLLER_H
#define CONTROLLER_H

class Model;

class Controller
{
public:
    Controller(Model *pModel);
    void newGame();
    void tryToSlide(int cursorX, int cursorY);
private:
    Model* _pModel;
};

#endif // CONTROLLER_H
