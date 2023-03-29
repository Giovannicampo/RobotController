#ifndef BACKBUTTON_H
#define BACKBUTTON_H

#include "widget.h"

class BackButton : public Widget
{
    private:
        bool toBeUpdated;
        int radius;
        std::function<void()> _onClick = [] { };
        uint16_t touch_x;
        uint16_t touch_y;
        uint16_t color;
        uint16_t bgcolor;


    public:
        BackButton(uint16_t x, uint16_t y, uint16_t color)
            : Widget(x,y)
        {
            this->toBeUpdated = true;
            this->radius = 25;
            this->color = color;
            this->bgcolor = TFT_BLACK;
        }

        bool contains(uint16_t x, uint16_t y)
        {
            return x >= (x_pos - radius) && x < (x_pos + radius) && y >= (y_pos - radius) && y < (y_pos + radius);
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

        void drawBackButton()
        {
            tft->fillCircle(x_pos, y_pos, radius, color);
            tft->fillCircle(x_pos, y_pos, radius-2, bgcolor);
            tft->fillTriangle(x_pos-5, y_pos+10, x_pos-5, y_pos-10, x_pos-15, y_pos, color);
            tft->fillRect(x_pos-5, y_pos-5, 20, 10, color);
            toBeUpdated = false;
        }

        void setOnClick(std::function<void()> cb){
            this->_onClick = cb;
        }

        void update()
        {
            if (!this->visible) {
                return;
            }

            if (toBeUpdated) {
                drawBackButton();
            }

            if(tft->getTouch(&touch_x, &touch_y) && contains(touch_x, touch_y)) {
                _onClick();
            }
        }
};

#endif