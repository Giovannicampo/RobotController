#ifndef BILANCIA_H
#define BILANCIA_H

#include "HX711.h"
#include "display.h"

class Display;

#define MAX_ZERO 100

class Bilancia
{
    private:
        HX711* _scale;
        Display* _display;

        long _zero;
        long read_scale();
        int do_scale();
    public:
        Bilancia(HX711* scale, Display* display);

        void do_zero();
        void update();
};

#endif