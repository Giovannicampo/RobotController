#ifndef WIDGET_H
#define WIDGET_H

#include <TFT_eSPI_ext.h>

class Widget {

    String _id;

    

    protected:
        uint16_t x_pos;
        uint16_t y_pos;
        TFT_eSPI* tft;
        bool visible;

    public:
        Widget() : Widget(0,0){};
        Widget(uint16_t x, uint16_t y);
        void setTFT(TFT_eSPI* tft);
        void setID(String id);
        virtual void update();
        String getID();
        bool operator== (const Widget& A) const;
        void hide();
        void show();
        virtual void addedToView();
        virtual void setToBeUpdate(bool update) = 0;
};

#endif