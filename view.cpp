#include "view.h"
#include "constantmodelinterface.h"
#include "controller.h"
#include <iostream>
#include <sstream>

View::View(ConstantModelInterface *cmodel, Controller *controller):
    _pcModel(cmodel), _pController(controller)
{
    if(initAllegro5())
    {
        _pDisplay = al_create_display(WINDOW_WIDTH, WINDOW_HEIGHT);
        if(!_pDisplay)
        {
             al_show_native_message_box(0, 0, 0, "Could not create Allegro Window", 0,0);
        }
        _pFont = al_load_font("Resources/Fonts/orbitron-light.ttf", FONT_SMALL_SIZE, 0);
        _pFontLarge = al_load_font("Resources/Fonts/orbitron-light.ttf", FONT_LARGE_SIZE, 0);
        al_set_window_position(_pDisplay, WINDOW_X, WINDOW_Y);
        al_set_window_title(_pDisplay, TITLE_OF_PROGRAM.c_str());
    }
}

View::~View()
{
    al_destroy_display(_pDisplay);
    al_destroy_font(_pFont);
    al_destroy_font(_pFontLarge);
}

void View::run()
{
    bool done{false};
    ALLEGRO_EVENT_QUEUE *event_queue = al_create_event_queue();
    al_register_event_source(event_queue, al_get_display_event_source(_pDisplay));
    al_register_event_source(event_queue, al_get_keyboard_event_source());
    al_register_event_source(event_queue, al_get_mouse_event_source());
    while(!done)
    {
        if(_draw)
        {
            al_clear_to_color(al_map_rgb(0,0,0));
            ALLEGRO_COLOR color = al_map_rgb(46, 150, 233);
            for(int i{0}; i < _pcModel->boardSizeX() * _pcModel->boardSizeY() - 1; ++i)
            {
                const Tile *t = _pcModel->getTileByIndex(i);
                al_draw_filled_rectangle(t->x(), t->y(),
                t->x() + SlidePuzzle::CELL_SIZE, t->y() + SlidePuzzle::CELL_SIZE,
                color);
                al_draw_filled_circle(t->x() + SlidePuzzle::CELL_SIZE / 2,
                               t->y() + SlidePuzzle::CELL_SIZE / 2,
                               SlidePuzzle::CELL_SIZE * 2 / 5,
                               al_map_rgb(66,114,229));
                if(t->number() <= 9)
                {
                    al_draw_text(_pFontLarge, al_map_rgb(0,0,0),t->number() == 1 ?
                                     t->x() + SlidePuzzle::CELL_SIZE * 2 / 5:
                                     t->x() + SlidePuzzle::CELL_SIZE * 1 / 3,
                                 t->y() + SlidePuzzle::CELL_SIZE * 1 / 3, 0,
                                 std::to_string(t->number()).c_str());
                }
                else
                {
                    al_draw_text(_pFontLarge, al_map_rgb(0,0,0),t->number() == 11 ?
                                     t->x() + SlidePuzzle::CELL_SIZE * 3 / 10 :
                                     t->x() + SlidePuzzle::CELL_SIZE * 1 / 5,
                                 t->y() + SlidePuzzle::CELL_SIZE * 1 / 3, 0,
                                 std::to_string(t->number()).c_str());
                }
            }
            std::stringstream ss;
            ss << "Moves number: " << _pcModel->getNumSlides();
            al_draw_text(_pFont, al_map_rgb(255, 0, 0),20,WINDOW_HEIGHT - 40, 0,
                         ss.str().c_str());
            if(_pcModel->isWin())
                al_draw_text(_pFontLarge, al_map_rgb(255,255,0), (WINDOW_WIDTH - 400) / 2, WINDOW_HEIGHT / 2 - 100,
                             0, "YOU WON!!!");
            al_flip_display();
            _draw = false;
        }

        ALLEGRO_EVENT events;
        al_wait_for_event(event_queue, &events);
        if(events.type == ALLEGRO_EVENT_KEY_UP)
        {
            switch(events.keyboard.keycode)
            {
               case ALLEGRO_KEY_ESCAPE :
                    done = true;
                    break;
               case ALLEGRO_KEY_N:
                    _pController->newGame();
                    _draw = true;
                    break;
               default:
                    break;
            }
        }
        else if(events.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
        {
            break;
            done = true;
        }
        else if(events.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP)
        {
            int cursorX = events.mouse.x;
            int cursorY = events.mouse.y;
            _pController->tryToSlide(cursorX, cursorY);
        }
    }
}

void View::updateView()
{
    _draw = true;
}

bool View::initAllegro5()
{
    if(!al_init())
    {
        al_show_native_message_box(0,0,0, "Could not initialize Allegro 5", 0, 0);
        return false;
    }
    al_init_font_addon();
    al_init_ttf_addon();
    al_init_primitives_addon();
    al_install_keyboard();
    al_install_mouse();
    return true;
}
