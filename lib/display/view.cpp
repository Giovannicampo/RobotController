#include "view.h"

View::View(String name)
{
    this->name = name;
    this->widgets = ArrayList<Widget*>();
}

String View::_color = "blue";
String View::_strategy = "GAMMA";
int View::numPalline = 0;
uint8_t View::tx_flag = IDLE_TX; 
bool View::_enabled = false;

t_can_score_data View::score_grande = {0,0,0,0};
t_can_score_data View::score_piccolo = {0,0,0,0};
t_can_robot_position View::positionPiccolo = {0,0,0,0,0};
t_can_robot_position View::positionGrande = {0,0,0,0,0};
t_can_robot_battery View::batteryPiccolo = {0};

int init_data[2] = {-1,-1};
int* View::_configuration = init_data;

String View::getName()
{
    return this->name;
}

void View::addWidget(Widget* widget){
    widget->setTFT(this->tft);
    widget->setID(this->getName()+"_"+this->id_widget);
    widget->addedToView();
    this->id_widget++;
    this->widgets.add(widget);
}

void View::removeWidget(Widget* widget){
    this->widgets.remove(widget);
}

void View::update(){
    for (int i = 0; i < this->widgets.size(); i++) {
        this->widgets[i]->update();
    }
}

void View::setTFT(TFT_eSPI* tft){
    this->tft = tft;
};

TFT_eSPI* View::getTFT(){
    return this->tft;
}

void View::setDisplay(Display* display){
    this->display = display;
}

void View::setCurrentStrategy(String stgy)
{
    Serial.println("strategy setted to " + stgy);
    _strategy = stgy;

    // gestire tx ai robot
}

String View::getCurrentStrategy()
{
    Serial.println("strategy is: " + _strategy);
    return _strategy;
}

void View::setColor(String color)
{
    Serial.println("color setted to " + color);
    _color = color;

    // gestire tx ai robot
}

String View::getColor()
{
    Serial.println("color is: " + _color);
    return _color;
}

void View::setConfiguration(int* config)
{
    _configuration[0] = config[0];
    _configuration[1] = config[1];
    Serial.print("configuration setted to ");
    Serial.print(_configuration[0]);
    Serial.println(_configuration[1]);

    // gestire tx ai robot
}

t_can_strategy_command* View::packAlign(uint8_t index)
{
    int* config = getConfiguration();

    t_can_strategy_command* data = new t_can_strategy_command();

    // setting command
    data->cmd = index == 0 ? STRATEGY_COMMAND_ALIGN_PICCOLO : STRATEGY_COMMAND_ALIGN_GRANDE1;

    // color
    if(_color == GREEN){
        data->flags = 0;
    } 
    else if(_color == BLUE){
        data->flags = 1;
    }

    // setting elapsed time
    data->elapsed_time = 0;

    // setting strategy
    if(_strategy == ALPHA_STRATEGY){
        data->stgy = 1;
    }
    else if(_strategy == BETA_STRATEGY){
        data->stgy = 2;
    }
    else if(_strategy == GAMMA_STRATEGY){
        data->stgy = 3;
    }
    else if(_strategy == DELTA_STRATEGY){
        data->stgy = 4;
    }

    // setting align configuration
    int robot_conf = index == 0 ? config[0] : config[1];
    switch(robot_conf)
    {
        case 1:
        case 10:
            data->align = 1;
            break;
        case 2:
        case 9:
            data->align = 2;
            break;
        case 3:
        case 8:
            data->align = 3;
            break;
        case 4:
        case 7:
            data->align = 4;
            break;
        case 5:
        case 6:
            data->align = 5;
            break;
    }

    // value padding
    data->padding[0] = 0;
    data->padding[1] = 0;
    return data;
}

uint8_t* View::txAlignGrande()
{
    if(tx_flag != ALIGN_GRANDE_TX){
        return nullptr;
    }
    int* config = getConfiguration();
    if(config[1] == -1){
        Serial.println("txAlignGrande not possible, config not found");
        tx_flag = IDLE_TX;
        return nullptr;
    }
    t_can_strategy_command* data = packAlign(1);
    return (uint8_t *)data;
}

uint8_t* View::txAlignPiccolo()
{
    if(tx_flag != ALIGN_PICCOLO_TX){
        return nullptr;
    }
    int* config = getConfiguration();
    if(config[0] == -1){
        Serial.println("txAlignPiccolo not possible, config not found");
        tx_flag = IDLE_TX;
        return nullptr;
    }
    t_can_strategy_command* data = packAlign(0);
    return (uint8_t *)data;
}

uint8_t* View::txEnable()
{
    if(tx_flag != ENABLE_TX){
        return nullptr;
    }
    int* config = getConfiguration();
    if(config[0] == -1 || config[1] == -1){
        Serial.println("txEnable not possible, config not found");
        tx_flag = IDLE_TX;
        return nullptr;
    }
    t_can_strategy_command* data = new t_can_strategy_command();
    data->cmd = STRATEGY_COMMAND_ENABLE_STARTER;

    // trash data
    data->flags = 0;
    data->elapsed_time = 0;
    data->stgy = 0;
    data->align = 0;
    data->padding[0] = 0;
    data->padding[1] = 0;

    return (uint8_t *)data;
}

void View::setTxFlag(uint8_t flag)
{
    tx_flag = flag;
}

void View::clearScreen()
{
    this->tft->fillScreen(bgColor);
}

int* View::getConfiguration()
{
    Serial.print("configuration is: ");
    Serial.print(_configuration[0]);
    Serial.println(_configuration[1]);
    return _configuration;
}

void View::setEnabled(bool state)
{
    String s = state == true ? "true" : "false";
    Serial.println("Robot enable is " + s);
    _enabled = state;
}

bool View::getEnabled()
{
    return _enabled;
}

void View::setTCanRobotPosition(t_can_robot_position pos, uint8_t index)
{
    if(index == PICCOLO_INDEX){
        positionPiccolo = pos;
    }
    else if(index == GRANDE_INDEX){
        positionGrande = pos;
    }
}

t_can_robot_position View::getTCanRobotPositionPiccolo()
{
    return positionPiccolo;
}

t_can_robot_position View::getTCanRobotPositionGrande()
{
    return positionGrande;
}

void View::setTCanRobotBattery(t_can_robot_battery bat)
{
    batteryPiccolo = bat;
}

t_can_robot_battery View::getTCanRobotBatteryPiccolo()
{
    return batteryPiccolo;
}

void View::setScorePiccolo(t_can_score_data s)
{
    score_piccolo = s;
}

t_can_score_data View::getScorePiccolo()
{
    return score_piccolo;
}

void View::setScoreGrande(t_can_score_data s)
{
    score_grande = s;
}

t_can_score_data View::getScoreGrande()
{
    return score_grande;
}

void View::setNumPalline(int num)
{
    numPalline = num;
}

int View::getNumPalline()
{
    return numPalline;
}

