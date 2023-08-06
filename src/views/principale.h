#ifndef PRINCIPALE_H
#define PRINCIPALE_H

#include <Arduino.h>
#include <TFT_eSPI.h>
#include "display.h"
#include "widgets/label.h"
#include "widgets/battery.h"
#include "widgets/button.h"

class Principale : public View
{
    private:
        Label* label_piccolo;
        Label* label_piccolo_x;
        Label* label_piccolo_y;
        Label* label_piccolo_t;
        Label* label_grande;
        Label* label_grande_x;
        Label* label_grande_y; 
        Label* label_grande_t;
        Label* strategy;

        Battery* battery_piccolo;
        Battery* battery_grande;

        Button* color;
        Button* align;
        Button* stgy;
        Button* enable;

        bool screenChanged;

        void setPos();

    public:
    Principale();

    void setScreenChanged(bool state);

    //Override da View
    void update();

    void setBatteryPiccolo();
    int getBatteryGrande();

    void setStrategyLabel();
    void setColorButton();
};

#endif