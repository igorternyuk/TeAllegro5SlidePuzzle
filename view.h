#ifndef VIEW_H
#define VIEW_H

#include <string>
#include "modellistener.h"
#include <allegro5/allegro.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>

class ConstantModelInterface;
class Controller;

class View : public ModelListener
{
public:
    View(ConstantModelInterface *cmodel, Controller *controller);
    ~View();
    void run();
    virtual void updateView();
private:
    enum {
        WINDOW_WIDTH = 595,
        WINDOW_HEIGHT = 640,
        WINDOW_X = 200,
        WINDOW_Y = 100,
        FONT_SMALL_SIZE = 40,
        FONT_LARGE_SIZE = 60
    };
    const std::string TITLE_OF_PROGRAM = "SlidePuzzle";
    bool _draw{true};
    ConstantModelInterface *_pcModel;
    Controller *_pController;
    ALLEGRO_DISPLAY *_pDisplay;
    ALLEGRO_FONT *_pFont;
    ALLEGRO_FONT *_pFontLarge;
    bool initAllegro5();
};

#endif // VIEW_H
