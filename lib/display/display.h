
#ifndef DISPLAY_H
#define DISPLAY_H

#include "view.h"
#include "Arduino.h"
#include "bilancia.h"
#include "displayDefines.h"
#include "controller.h"

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
    Controller* controller;
    Bilancia* bilancia;
    uint16_t touch_x;
    uint16_t touch_y;
    uint16_t bgcolor = TFT_BLACK;

    public:
    Display(TFT_eSPI* tft, View* view_list[], int num);
    void update();
    void setTFT(TFT_eSPI* tft);
    void setController(Controller* controller);
    void changeView(String name);
    View* getCurrentView();
    View* getView(String view);
    void onRadioReceive(uint8_t* data, uint16_t addr_robot);
    uint8_t * onRadioTransmit();
    void callTrasmission();
    void onBilanciaReceive(int numPalline);
    void setTxFlag(bool state);
}; 

#endif