#include "display.h"

Display::Display(TFT_eSPI* tft, View* view_list[], int num)
{
    this->views = view_list;
    this->first_view = 3;
    this->current_view = this->first_view;
    this->num_views = num;
    this->tft = tft;

    for(uint i=0; i<num_views; i++)
    {
        this->views[i]->setTFT(this->tft);
        this->views[i]->setDisplay(this);
    }
}

void Display::update()
{
    views[current_view]->update();
}

void Display::changeView(String name)
{
    this->tft->fillScreen(bgcolor);
    for(uint i=0; i<num_views; i++)
    {
        if(this->views[i]->getName() == name)
        {
            this->current_view = i;
            break;
        }
    }
}

void Display::setTFT(TFT_eSPI* tft){
    this->tft = tft;
}

void Display::setController(Controller* controller)
{
    this->controller = controller;
}

View* Display::getCurrentView()
{
    return views[current_view];
}

View* Display::getView(String view)
{
    for(uint i=0; i<num_views; i++)
    {
        if(view == views[i]->getName()) {return views[i];}
    }
    return nullptr;
}

void Display::onRadioReceive(uint8_t* data, uint16_t addr_robot)
{
    uint8_t check = 0;
    for(unsigned int i=0; i<10; i++){
        check += data[i];
    }
    if(data[10] != check){
        return;
    }
    // robot position handling
    if (data[0] == HEAD_PICCOLO_POS && data[1] == TAIL_PICCOLO_POS)
    {
        t_can_robot_position * pos = (t_can_robot_position *)&data[2];
        // Serial.println(pos->flags);
        if(addr_robot == PICCOLO_ADDRESS){
            View::setTCanRobotPosition(*pos,PICCOLO_INDEX);
        }
        else if(addr_robot == GRANDE_ADDRESS){
            View::setTCanRobotPosition(*pos,GRANDE_INDEX);
        }
    }
    else if(data[0] == HEAD_GRANDE_POS && data[1] == TAIL_GRANDE_POS)
    {
        t_can_robot_position * pos = (t_can_robot_position *)&data[2];
        // Serial.println(pos->x);
        if(addr_robot == PICCOLO_ADDRESS){
            View::setTCanRobotPosition(*pos,PICCOLO_INDEX);
        }
        else if(addr_robot == GRANDE_ADDRESS){
            View::setTCanRobotPosition(*pos,GRANDE_INDEX);
        }
    }

    // robot battery
    else if(data[0] == HEAD_PICCOLO_BAT && data[1] == TAIL_PICCOLO_BAT)
    {
        
        t_can_robot_battery * bat = (t_can_robot_battery *)&data[2];
        if(addr_robot == PICCOLO_ADDRESS){
            View::setTCanRobotBattery(*bat);
        }
        else if(addr_robot == GRANDE_ADDRESS){
            // da gestire
        }
    }

    // score counter
    else if(data[0] == HEAD_SCORE && data[1] == TAIL_SCORE)
    {
        if(addr_robot == PICCOLO_ADDRESS){
            t_can_score_data * score = (t_can_score_data *)&data[2];
            Serial.printf("[Controller] Score piccolo: %d\n", score->score);
            View::setScorePiccolo(*score);

        }else if(addr_robot == GRANDE_ADDRESS){
            t_can_score_data * score = (t_can_score_data *)&data[2];
            Serial.printf("[Controller] Score grande: %d\n", score->score);
            View::setScoreGrande(*score);
        }
    }


    Serial.printf("[Controller] Packet received: %#x ",data[1]);
    Serial.printf("%#x\n",(data[0]));
}

void Display::callTrasmission()
{
    this->controller->onTrasmission();
}

uint8_t* Display::onRadioTransmit()
{
    if(View::txAlignPiccolo() != nullptr){
        Serial.println("align piccolo tx");
        return View::txAlignPiccolo();
    }
    
    if(View::txAlignGrande() != nullptr){
        Serial.println("align grande tx");
        return View::txAlignGrande();
    }
    
    if(View::txEnable() != nullptr){
        Serial.println("enable tx");
        return View::txEnable();
    }

    return nullptr;
}

void Display::onBilanciaReceive(int numPalline)
{
    View::setNumPalline(numPalline);
}

void Display::setTxFlag(bool state)
{
    if(!state){
        View::setTxFlag(IDLE_TX);
    }
    return;
}