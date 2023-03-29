
#ifndef DISPLAY_H
#define DISPLAY_H

#include "view.h"
#include "Arduino.h"

class View;
class Bilancia;
class Controller;

class Display
{
    View** views;
    uint num_views;
    uint first_view;
    uint current_view;
    TFT_eSPI* tft;
    uint16_t touch_x;
    uint16_t touch_y;
    uint16_t bgcolor = TFT_BLACK;

    public:
    Display(TFT_eSPI* tft, View* view_list[], int num);
    void update();
    void setTFT(TFT_eSPI* tft);
    void changeView(String name);
    View* getCurrentView();
    View* getView(String view);
}; 

#endif