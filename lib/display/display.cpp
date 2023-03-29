#include "display.h"

Display::Display(TFT_eSPI* tft, View* view_list[], int num)
{
    this->views = view_list;
    this->first_view = 0;
    this->current_view = this->first_view;
    this->num_views = num;
    this->tft = tft;

    for(uint i=0; i<num_views; i++)
    {
        this->views[i]->setTFT(this->tft);
        this->views[i]->setDisplay(this);
    }
}

void Display::update()
{
    views[current_view]->update();
}

void Display::changeView(String name)
{
    this->tft->fillScreen(bgcolor);
    for(uint i=0; i<num_views; i++)
    {
        if(this->views[i]->getName() == name)
        {
            this->current_view = i;
            break;
        }
    }
}

void Display::setTFT(TFT_eSPI* tft){
    this->tft = tft;
}

View* Display::getCurrentView()
{
    return views[current_view];
}

View* Display::getView(String view)
{
    for(uint i=0; i<num_views; i++)
    {
        if(view == views[i]->getName()) {return views[i];}
    }
    return nullptr;
}
