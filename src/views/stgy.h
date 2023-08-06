#ifndef STGY_H
#define STGY_H

#include <Arduino.h>
#include <TFT_eSPI.h>
#include "display.h"
#include "bitmap.h"
#include "widgets/label.h"
#include "widgets/button.h"
#include "widgets/backbutton.h"
#include "widgets/picture.h"

class Stgy : public View
{
    private:
        Button* alpha;
        Button* beta;
        Button* gamma;
        Button* delta;
        BackButton* back;

        Label* strategy;

        Picture* cake;

        bool screenChanged;

    public:
        Stgy();

        //Override da View
        void setScreenChanged(bool state);

        void setStrategy(String stgy);

        void update();
};

#endif