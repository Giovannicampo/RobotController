#ifndef SLIDER_H
#define SLIDER_H

#include "widget.h"

class Slider : public Widget
{
    private:
        bool toBeUpdated;
        uint16_t touch_x;
        uint16_t touch_y;
        uint16_t width;
        uint16_t height;

        std::function<void()> _leftPiccolo = [] { };
        std::function<void()> _rightGrande = [] { };
    
    public:
        Slider(uint16_t x, uint16_t y)
            : Widget(x,y)
        {
            this->width = 80;
            this->height = 40;
        }

        //Override da widget
        void setToBeUpdate(bool update)
        {
            toBeUpdated = update;
        }

        void setOnClick(std::function<void()> cb, int index){
            if (index == 1) {
                this->_leftPiccolo = cb;
            } else if (index == 2) {
                this->_rightGrande = cb;
            }
        }

        bool contains(uint16_t x, uint16_t y)
        {
            return x >= x_pos+19 && x < x_pos+61 && y > y_pos && y < y_pos+40;
        }

        bool containsLeft(uint16_t x, uint16_t y)
        {
            return x > x_pos && x < x_pos+40 && touch_y > y_pos && touch_y < y_pos+40;
        }

        bool containsRight(uint16_t x, uint16_t y)
        {
            return x >= x_pos+40 && x <= x_pos+80 && touch_y > y_pos && touch_y < y_pos+40;
        }

        void drawLabel(uint8_t x, uint8_t y, uint16_t color, uint16_t bgcolor, String label)
        {
            tft->setCursor(x,y); //centrato
            tft->setTextSize(3);
            tft->setTextColor(color, bgcolor);
            tft->print(label);
        }

        void drawSlider()
        {
            tft->fillRoundRect(x_pos,y_pos,width,height,20,TFT_WHITE);
            tft->fillRoundRect(x_pos+2,y_pos+2,width-4,height-4,18,TFT_BLACK);
            if(!tft->getTouch(&touch_x, &touch_y))
            {
                tft->fillCircle(x_pos+19,y_pos+19,15,TFT_ORANGE);
                drawLabel(x_pos-20,y_pos+10,TFT_YELLOW,TFT_BLACK,"P");
                _leftPiccolo();
            }

            toBeUpdated = false;
        }

        void update(){
            if(toBeUpdated) drawSlider();
            
            if(tft->getTouch(&touch_x, &touch_y) && contains(touch_x,touch_y))
            {
                tft->fillRoundRect(x_pos+2,y_pos+2,width-4,height-4,18,TFT_BLACK);
                tft->fillCircle(touch_x,y_pos+19,15,TFT_ORANGE); 
            }

            if(tft->getTouch(&touch_x, &touch_y) && containsLeft(touch_x,touch_y)){
                drawLabel(x_pos-20,y_pos+10,TFT_YELLOW,TFT_BLACK,"P");
                drawLabel(x_pos+90,y_pos+10,TFT_BLACK,TFT_BLACK,"G");
                 _leftPiccolo();
            }
            else if(tft->getTouch(&touch_x, &touch_y) && containsRight(touch_x,touch_y)){
                drawLabel(x_pos+90,y_pos+10,TFT_YELLOW,TFT_BLACK,"G");
                drawLabel(x_pos-20,y_pos+10,TFT_BLACK,TFT_BLACK,"P");
                 _rightGrande();
            }
        }
};

#endif