#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "mrf24j.h"
#include "display.h"
#include "ArrayList.h"

class Display;

// #define PICCOLO_ADDRESS 0x4312
// #define GRANDE_ADDRESS 0x1243

class Controller
{
    protected:
    Mrf24j* mrf;
    Display* display;

    public:
    Controller(Mrf24j* mrf, Display* display);

    void handleRx();
    void handleTx();
    void onReceive(uint8_t* _data, uint16_t addr_robot);
    uint8_t* onTrasmission();
};

#endif