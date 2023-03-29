#ifndef VIEW_H
#define VIEW_H

#include <Arduino.h>
#include <widget.h>
#include <TFT_eSPI.h>
#include <ArrayList.h>
#include "display.h"

class Display;

class View 
{
    String name;
    ArrayList<Widget*> widgets;
    TFT_eSPI* tft;
    uint id_widget = 0x00;

    protected:
        Display* display;
        uint16_t bgColor = TFT_BLACK;

    public:
        View(String name);
        String getName();
        void addWidget(Widget* widget);
        void removeWidget(Widget* widget);
        virtual void update();
        void setTFT(TFT_eSPI* tft);
        TFT_eSPI* getTFT();
        void setDisplay(Display* display);
        void clearScreen();

        
        virtual void setScreenChanged(bool state) = 0;
};

#endif