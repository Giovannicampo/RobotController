#ifndef XPOS_H
#define XPOS_H

#include "widget.h"

class XPos : public Widget
{
    private:
        bool toBeUpdated;
        uint16_t _width;
        uint16_t _height;
        uint16_t _color;

    public:
        XPos(uint16_t x, uint16_t y, uint16_t color)
            : Widget(x,y)
        {
            this->_width = 15;
            this->_height = 15;
            this->_color = color;
        }

        //Override da widget
        void setToBeUpdate(bool update)
        {
            toBeUpdated = update;
        }

        void setX(uint16_t x)
        {
            this->x_pos = x;
        }

        void setY(uint16_t y)
        {
            this->y_pos = y;
        }

        void drawX()
        {
            tft->fillCircle(x_pos + _width/2, y_pos + _height/2, 10, _color);
            tft->drawLine(x_pos, y_pos, x_pos+_width, y_pos+_height, TFT_WHITE);
            tft->drawLine(x_pos, y_pos+_height, x_pos+_width, y_pos, TFT_WHITE);
        }

        void update()
        {
            if(!this->visible) return;
            if(toBeUpdated) drawX();
        }
};

#endif