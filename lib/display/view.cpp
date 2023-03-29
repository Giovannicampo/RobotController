#include "view.h"

View::View(String name)
{
    this->name = name;
    this->widgets = ArrayList<Widget*>();
}


String View::getName()
{
    return this->name;
}

void View::addWidget(Widget* widget){
    widget->setTFT(this->tft);
    widget->setID(this->getName()+"_"+this->id_widget);
    widget->addedToView();
    this->id_widget++;
    this->widgets.add(widget);
}

void View::removeWidget(Widget* widget){
    this->widgets.remove(widget);
}

void View::update(){
    for (int i = 0; i < this->widgets.size(); i++) {
        this->widgets[i]->update();
    }
}

void View::setTFT(TFT_eSPI* tft){
    this->tft = tft;
};

TFT_eSPI* View::getTFT(){
    return this->tft;
}

void View::setDisplay(Display* display){
    this->display = display;
}

void View::clearScreen()
{
    this->tft->fillScreen(bgColor);
}