#ifndef LABEL_H
#define LABEL_H
#include "widget.h"
#include <Arduino.h>

class Label: public Widget{

    String _label;
    uint16_t _color;
    uint16_t _bgcolor;
    uint8_t _size;
    bool toBeUpdated;

    public:

    Label()
        : Widget(0,0)
    {
        this->_color = TFT_WHITE;
        this->_bgcolor = TFT_BLACK;
        this->_size = 1;
        this->_label = "";
        this->toBeUpdated = true;
    }

    Label(int x, int y, uint16_t color,uint16_t bgcolor, uint8_t size, String label)
        : Widget(x, y)
    {
        this->_color = color;
        this->_bgcolor = bgcolor;
        this-> _size = size;
        this->_label = label;
    }

    void setToBeUpdate(bool update)
    {
        toBeUpdated = update;
    }

    void setText(String label){
        this->_label = label;
    };

    void setColor(uint16_t color, uint16_t bgcolor)
    {
        this->_color=color;
        this->_bgcolor = bgcolor;
    }

    void setSize(uint8_t size)
    {
        this->_size = size;
    }

    void setPosition(int x, int y)
    {
        this->x_pos = x;
        this->y_pos = y;
    }

    void drawLabel()
    {
        tft->setCursor(x_pos,y_pos); //centrato
        tft->setTextSize(_size);
        tft->setTextColor(_color, _bgcolor);
        tft->print(_label);
        toBeUpdated = false;
    }

    void update(){
        Widget::update();

        if (!visible) {
            return;
        }

        if (toBeUpdated) {
            drawLabel();
        }
    }

};

#endif