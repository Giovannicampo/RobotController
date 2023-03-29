#include "widget.h"


Widget::Widget(uint16_t x, uint16_t y){
    this->tft = nullptr;
    this->x_pos = x;
    this-> y_pos = y;
    this->visible = true;
};


void Widget::addedToView(){};

void Widget::setTFT(TFT_eSPI* tft){
    this->tft = tft;
};

void Widget::update(){
    if(this->tft == nullptr){
        return;
    }
}

void Widget::setID(String id){
    this->_id = id;
}

String Widget::getID(){
    return this->_id;
}

bool Widget::operator== (const Widget& A) const{
    return this->_id == A._id;
}

void Widget::hide()
{
    this->visible = false;
}

void Widget::show()
{
    this->visible = true;
}
