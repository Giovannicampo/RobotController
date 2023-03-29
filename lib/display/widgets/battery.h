#ifndef BATTERY_H
#define BATTERY_H

#include "widget.h"

class Battery : public Widget
{
    private:
    int width;
    int height;
    int value;
    bool valuechange;
    int millisecondi;
    int color;

    public:
    Battery(int x, int y, int value)
        : Widget(x,y)
    {
        width = 26;
        height = 10;
        this->value = value;
        millisecondi = millis();
        color = TFT_RED;
        valuechange = false;
    }

    void setValue(int value)
    {
        value = value < 0 ? 0 : value;
        value = value > 100 ? 100 : value;
        if(this->value == value){
            return;
        }
        this->value = value;
        tft->fillRect(x_pos+40, y_pos-2,40,15,TFT_BLACK);
        valuechange = true;
    }

    void incrementvalue()
    {
        value++;
        if(value > 100){value = 100;}
        valuechange = true;
    }

    void decrementvalue()
    {
        value--;
        if(value < 0) {value = 0;}
        valuechange = true;
    }

    void setToBeUpdate(bool update){}

    void update()
    {
        Widget::update();

        if (!visible) {
            return;
        }

        tft->drawRect(x_pos, y_pos, width, height, TFT_WHITE);

        uint16_t first_pos = x_pos+2;
        uint16_t offset = 4;

        if (value < 15)
        {
            int mil = millis();
            if (mil-millisecondi >= 500) {
                tft->fillRect(first_pos, y_pos+2, 2, 6, color);
                color = color == TFT_RED ? TFT_BLACK : TFT_RED;
                millisecondi = mil;
            }
        }
        else if (value > 15) {
            tft->fillRect(first_pos, y_pos+2, 2, 6, TFT_RED);
        }

        int _color = value > 25 ? TFT_YELLOW : TFT_BLACK;
        tft->fillRect(first_pos + offset, y_pos+2, 2, 6, _color);

        _color = value > 40 ? TFT_YELLOW : TFT_BLACK;
        tft->fillRect(first_pos + offset*2, y_pos+2, 2, 6, _color);

        _color = value > 50 ? TFT_GREEN : TFT_BLACK;
        tft->fillRect(first_pos + offset*3, y_pos+2, 2, 6, _color);

        _color = value > 70 ? TFT_GREEN : TFT_BLACK;
        tft->fillRect(first_pos + offset*4, y_pos+2, 2, 6, _color);

        _color = value > 90 ? TFT_GREEN : TFT_BLACK;
        tft->fillRect(first_pos + offset*5, y_pos+2, 2, 6, _color);

        tft->fillRect(x_pos+26, y_pos+3, 2, 4, TFT_WHITE);

        tft->setCursor(x_pos+40, y_pos-2);
        tft->setTextColor(TFT_WHITE, TFT_BLACK);
        tft->setTextSize(2);
        if(valuechange)
        {
            tft->print("   ");
            valuechange = false;
        }
        tft->setCursor(x_pos+40, y_pos-2);
        tft->print(value);
    }

};

#endif