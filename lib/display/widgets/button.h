#ifndef BUTTON_H
#define BUTTON_H

#include "widget.h"


class Button : public Widget
{
    private:
        uint16_t width;
        uint16_t height;
        uint16_t dimOutline;
        uint16_t outline;
        uint16_t fill;
        uint16_t textColor;
        bool centered;
        uint8_t textSize;
        String label;
        uint8_t _textdatum;
        int16_t  _xd, _yd; 
        bool toBeUpdated;

        uint16_t touch_x;
        uint16_t touch_y;
        std::function<void()> _onClick = [] { };

    public:


        Button(uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint16_t outline, uint16_t dimOutline, uint16_t fill, uint16_t textcolor, String label, uint8_t textsize, bool fromCenter)
        : Widget(x,y), centered(fromCenter), label(label), outline(outline), fill(fill), textColor(textcolor), textSize(textsize), dimOutline(dimOutline)
        {
            this->width = width ; //label.length() * 18.7;//width; //.length() * textsize * 7;
            this->height = height; // 14 * textsize;
            this->_textdatum = MC_DATUM;
            _xd = 0;
            _yd = 0;
            toBeUpdated = true;        
        };

        int getPosX()
        {
            return x_pos;
        }

        int getPosY()
        {
            return y_pos;
        }

        int getWidth()
        {
            return width;
        }

        int getHeight()
        {
            return height;
        }

        void setFillColor(uint16_t color)
        {
            this->fill = color;
        }

        uint16_t getFillColor()
        {
            return this->fill;
        }

        bool contains(uint16_t x, uint16_t y)
        {
            return x >= x_pos && x < (x_pos + width) && y >= y_pos && y < (y_pos + height);
        }

        void setToBeUpdate(bool update)
        {
            toBeUpdated = update;
        }


        void drawButton() {

            uint8_t cornerRadius = min(width, height) / 4;
            if (this->dimOutline > 0) tft->fillSmoothRoundRect(x_pos, y_pos, width, height, cornerRadius, outline, this->fill);
            tft->fillSmoothRoundRect(x_pos+dimOutline, y_pos+dimOutline, width-(2*dimOutline), height-(2*dimOutline), cornerRadius-dimOutline, fill, outline);

            if (tft->textfont == 255) {
                tft->setCursor(x_pos + (width / 8),
                                y_pos + (height / 4));
                tft->setTextColor(textColor);
                tft->setTextSize(textSize);
                tft->print(label);
            }
            else {
                tft->setTextColor(textColor, fill);
                tft->setTextSize(textSize);

                uint8_t tempdatum = tft->getTextDatum();
                tft->setTextDatum(_textdatum);
                uint16_t tempPadding = tft->getTextPadding();
                tft->setTextPadding(0);

                tft->drawString(label, x_pos + (width/2) + _xd, y_pos + (height/2) + _yd);

                tft->setTextDatum(tempdatum);
                tft->setTextPadding(tempPadding);
            }
            toBeUpdated = false;
        }


        void setOnClick(std::function<void()> cb){
            this->_onClick = cb;
        }

        void update(){
            if(!this->visible) return;
            if(toBeUpdated) drawButton();
            if(tft->getTouch(&touch_x, &touch_y) && contains(touch_x, touch_y)){
                 _onClick();
            }
        }

};

#endif