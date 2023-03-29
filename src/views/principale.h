#ifndef PRINCIPALE_H
#define PRINCIPALE_H

#include <Arduino.h>
#include <TFT_eSPI.h>
#include "display.h"
#include "widgets/label.h"
#include "widgets/battery.h"
#include "widgets/button.h"
#include "widgets/slider.h"

class Principale : public View
{
    private:

        Label* title;
        Label* lorem;

        Battery* battery;

        Slider* slider;

        bool screenChanged;

    public:
    Principale();

    void setScreenChanged(bool state);

    //Override da View
    void update();
};

#endif