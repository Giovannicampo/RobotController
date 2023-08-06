#include "principale.h"
#include "sharedDefines.h"

Principale::Principale()
    : View(PRINCIPALE_VIEW)
{
    screenChanged = false;

    label_piccolo = new Label(20, 20, TFT_YELLOW, bgColor, 2, "PICCOLO");
    label_piccolo_x = new Label(20, 40, TFT_WHITE, bgColor, 2, "X: - - - -");
    label_piccolo_y = new Label(20, 60, TFT_WHITE, bgColor, 2, "Y: - - - -");
    label_piccolo_t = new Label(20, 80, TFT_WHITE, bgColor, 2, "T: - - - -");
    label_grande = new Label(180, 20, TFT_YELLOW, bgColor, 2, "GRANDE");
    label_grande_x = new Label(180, 40, TFT_WHITE, bgColor, 2, "X: - - - -");
    label_grande_y = new Label(180, 60, TFT_WHITE, bgColor, 2, "Y: - - - -");
    label_grande_t = new Label(180, 80, TFT_WHITE, bgColor, 2, "T: - - - -");
    strategy = new Label(130, 140, TFT_WHITE, bgColor, 2, "- - -");
    

    battery_piccolo = new Battery(50, 120, 10);
    battery_grande = new Battery(210, 120, 100);

    color = new Button(6, 200, 70, 30,TFT_YELLOW, 3, TFT_BLUE, TFT_WHITE, "COLOR", 2, false);
    align = new Button(86, 200, 70, 30,TFT_YELLOW, 3, TFT_ORANGE, TFT_WHITE, "ALIGN", 2, false);
    stgy = new Button(166, 200, 70, 30,TFT_YELLOW, 3, TFT_ORANGE, TFT_WHITE, "STGY", 2, false);
    enable = new Button(246, 200, 70, 30,TFT_YELLOW, 3, TFT_ORANGE, TFT_WHITE, "ENABLE", 2, false);

    addWidget(label_piccolo);
    addWidget(label_piccolo_x);
    addWidget(label_piccolo_y);
    addWidget(label_piccolo_t);
    

    addWidget(label_grande);
    addWidget(label_grande_x);
    addWidget(label_grande_y);
    addWidget(label_grande_t);

    addWidget(strategy);

    addWidget(battery_piccolo);
    addWidget(battery_grande);

    addWidget(color);
    addWidget(align);
    addWidget(stgy);
    addWidget(enable);

    stgy->setOnClick(([this]() {
        this->display->changeView(STRATEGY_VIEW);
        setScreenChanged(true);
    }));

    align->setOnClick(([this]() {
        this->display->changeView(ALIGN_VIEW);
        setScreenChanged(true);
    }));

    enable->setOnClick(([this]() {
        this->display->changeView(ENABLE_VIEW);
        setScreenChanged(true);
    }));

    color->setOnClick(([this]() {
        setColorButton();
    }));
}

void Principale::setBatteryPiccolo()
{
    //da configurare ricezione
    t_can_robot_battery bat = View::getTCanRobotBatteryPiccolo();
    short percentage = bat.battery_percentage;
    // Serial.println(percentage);
    battery_piccolo->setValue(percentage);
}

int Principale::getBatteryGrande()
{
    //da configurare ricezione
    return 90;
}

void Principale::setScreenChanged(bool state)
{
    this->screenChanged = state;
}

void Principale::setPos()
{
    t_can_robot_position posGrande = View::getTCanRobotPositionGrande();
    t_can_robot_position posPiccolo = View::getTCanRobotPositionPiccolo();

    label_piccolo_x->setToBeUpdate(true);
    label_piccolo_y->setToBeUpdate(true);
    label_piccolo_t->setToBeUpdate(true);

    label_grande_x->setToBeUpdate(true); 
    label_grande_y->setToBeUpdate(true); 
    label_grande_t->setToBeUpdate(true);

    char s[80];

    sprintf(s,"X: %5d    ",posPiccolo.x);
    label_piccolo_x->setText(s);
    sprintf(s,"Y: %5d    ",posPiccolo.y);
    label_piccolo_y->setText(s); 
    sprintf(s,"T: %5d    ",posPiccolo.deg100/100);
    label_piccolo_t->setText(s);     

    sprintf(s,"X: %5d    ",posGrande.x);
    label_grande_x->setText(s);
    sprintf(s,"Y: %5d    ",posGrande.y);
    label_grande_y->setText(s); 
    sprintf(s,"T: %5d    ",posGrande.deg100/100);
    label_grande_t->setText(s);     
}

void Principale::setStrategyLabel()
{
    String stgy = View::getCurrentStrategy();
    if(stgy != "") {strategy->setText(stgy);}
}

void Principale::setColorButton()
{
    color->setToBeUpdate(true);

    if (View::getColor() == BLUE) {
        View::setColor(GREEN);
        color->setFillColor(TFT_GREEN);
    }
    else if (View::getColor() == GREEN) {
        View::setColor(BLUE);
        color->setFillColor(TFT_BLUE);
    }
}


void Principale::update()
{
    if(screenChanged)
    {
        label_piccolo->setToBeUpdate(true);
        label_piccolo_x->setToBeUpdate(true);
        label_piccolo_y->setToBeUpdate(true);
        label_piccolo_t->setToBeUpdate(true);
        label_grande->setToBeUpdate(true); 
        label_grande_x->setToBeUpdate(true); 
        label_grande_y->setToBeUpdate(true); 
        label_grande_t->setToBeUpdate(true);
        strategy->setToBeUpdate(true);

        color->setToBeUpdate(true);
        align->setToBeUpdate(true);
        stgy->setToBeUpdate(true);
        enable->setToBeUpdate(true);

        setStrategyLabel();

        screenChanged = false;
    }

    setPos();
    setBatteryPiccolo();

    View::update();
}