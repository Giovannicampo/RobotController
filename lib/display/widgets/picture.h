#ifndef PICTURE_H
#define PICTURE_H

#include "widget.h"

class Picture : public Widget
{
    private:
        bool toBeUpdated;
        const unsigned char* bitmap;
        uint16_t width;
        uint16_t height;
        uint16_t color;
    
    public:
        Picture(uint16_t x, uint16_t y, const unsigned char* bitmap, uint16_t width, uint16_t height, uint16_t color)
            : Widget(x,y), width(width), height(height), bitmap(bitmap), color(color)
        {
            toBeUpdated = true;
        }

        //Override da widget
        void setToBeUpdate(bool update)
        {
            toBeUpdated = update;
        }

        void setPosition(uint16_t x, uint16_t y)
        {
            this->x_pos = x;
            this->y_pos = y;
        }

        void update()
        {
            Widget::update();
            if(toBeUpdated) 
            {
                tft->drawBitmap(x_pos, y_pos, bitmap, width, height, color); 
                toBeUpdated = false;
            }
        }
};

#endif