#include "principale.h"

Principale::Principale()
    : View("principale")
{
    screenChanged = false;

    title = new Label(20,40,TFT_YELLOW,TFT_BLACK, 3, "Title");
    lorem = new Label(20,80,TFT_CYAN,TFT_BLACK, 2, "Lorem ipsum dolor sit amet");

    battery = new Battery(50, 120, 15);

    slider = new Slider(10,180);
}

void Principale::setScreenChanged(bool state)
{
    this->screenChanged = state;
}

void Principale::update()
{
    if(screenChanged)
    {
       title->setToBeUpdate(true);
       lorem->setToBeUpdate(true);
       battery->setToBeUpdate(true);
       slider->setToBeUpdate(true);

        screenChanged = false;
    }

    View::update();
}