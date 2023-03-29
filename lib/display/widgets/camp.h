#ifndef CAMP_H
#define CAMP_H

#include "widget.h"
#include "unict_team_logo.h"
#include "sharedDefines.h"

class Camp : public Widget
{
    private:
        bool toBeUpdated;
        uint16_t touch_x;
        uint16_t touch_y;
        uint16_t width;
        uint16_t height;

        //zone del campo
        std::function<void()> _onClick1 = [] { };
        std::function<void()> _onClick2 = [] { };
        std::function<void()> _onClick3 = [] { };
        std::function<void()> _onClick4 = [] { };
        std::function<void()> _onClick5 = [] { };
        std::function<void()> _onClick6 = [] { };
        std::function<void()> _onClick7 = [] { };
        std::function<void()> _onClick8 = [] { };
        std::function<void()> _onClick9 = [] { };
        std::function<void()> _onClick10 = [] { };

    public:
        Camp(uint16_t x, uint16_t y)
        {
            this->x_pos = x;
            this->y_pos = y;
            this->width = 225;
            this->height = 150;
        }

        //Override da widget
        void setToBeUpdate(bool update)
        {
            toBeUpdated = update;
        }

        void setOnClick(std::function<void()> cb, int index){

            switch (index)
            {
                case Zone::BLUE_1:
                    this->_onClick1 = cb;
                    break;
                case Zone::GREEN_2:
                    this->_onClick2 = cb;
                    break;
                case Zone::BLUE_3:
                    this->_onClick3 = cb;
                    break;
                case Zone::GREEN_4:
                    this->_onClick4 = cb;
                    break;
                case Zone::BLUE_5:
                    this->_onClick5 = cb;
                    break;
                case Zone::GREEN_6:
                    this->_onClick6 = cb;
                    break;
                case Zone::BLUE_7:
                    this->_onClick7 = cb;
                    break;
                case Zone::GREEN_8:
                    this->_onClick8 = cb;
                    break;
                case Zone::BLUE_9:
                    this->_onClick9 = cb;
                    break;
                case Zone::GREEN_10:
                    this->_onClick10 = cb;
                    break;
                default:
                    break;
            }
        }

        int contains(uint16_t x, uint16_t y)
        {
            if (x >= x_pos && x < (x_pos + 32) && y >= y_pos+118 && y < (y_pos + 150)) {
                return Zone::BLUE_1;
            }

            if (x >= x_pos+64 && x < (x_pos + 96) && y >= y_pos+118 && y < (y_pos + 150)) {
                return Zone::GREEN_2;
            }

            if (x >= x_pos+128 && x < (x_pos + 160) && y >= y_pos+118 && y < (y_pos + 150)) {
                return Zone::BLUE_3;
            }

            if (x >= x_pos+192 && x < (x_pos + 225) && y >= y_pos+118 && y < (y_pos + 150)) {
                return Zone::GREEN_4;
            }

            if (x >= x_pos+192 && x < (x_pos + 225) && y >= y_pos+79 && y < (y_pos + 111)) {
                return Zone::BLUE_5;
            }

            if (x >= x_pos+192 && x < (x_pos + 225) && y >= y_pos+40 && y < (y_pos + 72)) {
                return Zone::GREEN_6;
            }

            if (x >= x_pos+192 && x < (x_pos + 225) && y >= y_pos && y < (y_pos + 32)) {
                return Zone::BLUE_7;
            }

            if (x >= x_pos+128 && x < (x_pos + 160) && y >= y_pos && y < (y_pos + 32)) {
                return Zone::GREEN_8;
            }

            if (x >= x_pos+64 && x < (x_pos + 96) && y >= y_pos && y < (y_pos + 32)) {
                return Zone::BLUE_9;
            }

            if (x >= x_pos && x < (x_pos + 32) && y >= y_pos && y < (y_pos + 32)) {
                return Zone::GREEN_10;
            }

            // nessuna zona
            return -1;
        }

        void drawCamp()
        {
            tft->fillRect(x_pos, y_pos, width, height, TFT_WHITE);

            // lato grande 1
            tft->fillRect(x_pos, y_pos, 32, 32, TFT_GREEN);
            tft->fillRect(x_pos+64, y_pos, 32, 32, TFT_BLUE);
            tft->fillRect(x_pos+128, y_pos, 32, 32, TFT_GREEN);
            tft->fillRect(x_pos+192, y_pos, 33, 32, TFT_BLUE);

            // lato grande 2
            tft->fillRect(x_pos, y_pos+118, 32, 32, TFT_BLUE);
            tft->fillRect(x_pos+64, y_pos+118, 32, 32, TFT_GREEN);
            tft->fillRect(x_pos+128, y_pos+118, 32, 32, TFT_BLUE);
            tft->fillRect(x_pos+192, y_pos+118, 33, 32, TFT_GREEN);

            // lato piccolo
            tft->fillRect(x_pos+192, y_pos+79, 33, 32, TFT_BLUE);
            tft->fillRect(x_pos+192, y_pos+40, 33, 32, TFT_GREEN);

            tft->drawBitmap(x_pos+90, y_pos+52, unict_team_logo, 50, 49, TFT_BLACK);

            toBeUpdated = false;
        }

        void update()
        {
            if(!this->visible) return;
            if(toBeUpdated) {drawCamp();}
            if(tft->getTouch(&touch_x, &touch_y)){
                switch(contains(touch_x, touch_y))
                {
                    case Zone::BLUE_1:
                        _onClick1();
                        break;
                    case Zone::GREEN_2:
                        _onClick2();
                        break;
                    case Zone::BLUE_3:
                        _onClick3();
                        break;
                    case Zone::GREEN_4:
                        _onClick4();
                        break;
                    case Zone::BLUE_5:
                        _onClick5();
                        break;
                    case Zone::GREEN_6:
                        _onClick6();
                        break;
                    case Zone::BLUE_7:
                        _onClick7();
                        break;
                    case Zone::GREEN_8:
                        _onClick8();
                        break;
                    case Zone::BLUE_9:
                        _onClick9();
                        break;
                    case Zone::GREEN_10:
                        _onClick10();
                        break;
                    default:
                        break;
                }
            }
        }
};

#endif