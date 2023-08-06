#include "align.h"
#include "sharedDefines.h"

Align::Align()
    : View(ALIGN_VIEW)
{
    selectedSetting = Setting::PICCOLO;
    screenChanged = false;
    changeDone = false;
    defaultStrategy = View::getCurrentStrategy();
    selectedColor = View::getColor();
    configuration = new int[2];
    configuration[0] = -1;
    configuration[1] = -1;

    set = new Button(6, 200, 70, 30,TFT_YELLOW, 3, TFT_ORANGE, TFT_WHITE, "SET", 2, false);
    alignPiccolo = new Button(240, 30, 70, 30,TFT_YELLOW, 3, TFT_ORANGE, TFT_WHITE, "A PIC", 2, false);
    alignGrande = new Button(240, 70, 70, 30,TFT_YELLOW, 3, TFT_ORANGE, TFT_WHITE, "A GRA", 2, false);
    back = new BackButton(277, 202, TFT_WHITE);
    camp = new Camp(0,0);
    piccolo = new Label(0,0,TFT_WHITE, TFT_BLUE, 3, "P");
    grande = new Label(0,0,TFT_WHITE, TFT_BLUE, 3, "G");
    slider = new Slider(130,190);

    configDefaultStrategy();

    addWidget(set);
    addWidget(alignPiccolo);
    addWidget(alignGrande);
    addWidget(back);
    addWidget(camp);
    addWidget(piccolo);
    addWidget(grande);
    addWidget(slider);

    set->setOnClick(([this]() {
        toggle_led();
        View::setConfiguration(configuration);
    }));

    alignPiccolo->setOnClick(([this]() {
        toggle_led();
        View::setTxFlag(ALIGN_PICCOLO_TX);
    }));

    alignGrande->setOnClick(([this]() {
        toggle_led();
        View::setTxFlag(ALIGN_GRANDE_TX);
    }));

    back->setOnClick(([this]() {
        this->display->changeView(PRINCIPALE_VIEW);
        setScreenChanged(true);
    }));

    slider->setOnClick(([this]() {
        Serial.println("setting piccolo attivo");
        setSetting(Setting::PICCOLO);
    }),1);

    slider->setOnClick(([this]() {
        Serial.println("setting grande attivo");
        setSetting(Setting::GRANDE);
    }),2);

    camp->setOnClick(([this]() {
            Serial.printf("cliccata zona %d\n", 1);
            setPositionStrategy(1);
        }), 1);

    camp->setOnClick(([this]() {
            Serial.printf("cliccata zona %d\n", 2);
            setPositionStrategy(2);
        }), 2);

    camp->setOnClick(([this]() {
            Serial.printf("cliccata zona %d\n", 3);
            setPositionStrategy(3);
        }), 3);

    camp->setOnClick(([this]() {
            Serial.printf("cliccata zona %d\n", 4);
            setPositionStrategy(4);
        }), 4);

    camp->setOnClick(([this]() {
            Serial.printf("cliccata zona %d\n", 5);
            setPositionStrategy(5);
        }), 5);

    camp->setOnClick(([this]() {
            Serial.printf("cliccata zona %d\n", 6);
            setPositionStrategy(6);
        }), 6);

    camp->setOnClick(([this]() {
            Serial.printf("cliccata zona %d\n", 7);
            setPositionStrategy(7);
        }), 7);

    camp->setOnClick(([this]() {
            Serial.printf("cliccata zona %d\n", 8);
            setPositionStrategy(8);
        }), 8);

    camp->setOnClick(([this]() {
            Serial.printf("cliccata zona %d\n", 9);
            setPositionStrategy(9);
        }), 9);

    camp->setOnClick(([this]() {
            Serial.printf("cliccata zona %d\n", 10);
            setPositionStrategy(10);
        }), 10);
}

void Align::setSetting(Setting state)
{
    this->selectedSetting = state;
}

void Align::setScreenChanged(bool state)
{
    this->screenChanged = state;
}

void Align::setPositionStrategy(int index)
{
    if ((index % 2 == 0 && selectedColor == BLUE) || (index % 2 != 0 && selectedColor == GREEN)) {
      return;
    }

    if(selectedSetting == Setting::PICCOLO)
    {
        if (configuration[0] == index) {
          return;
        }

        drawPosition(piccolo,index);
        configuration[0] = index;
    }
    else // setting grande attivo
    {
        if (configuration[1] == index) {
            return;
        }

        drawPosition(grande, index);
        configuration[1] = index;
    }

    changeDone = true;
}

void Align::drawPosition(Label* lab, int zone)
{
    int offset_y = 5;
    int offset_x = 8;

    switch (zone)
    {
        case Zone::BLUE_1:
            lab->setPosition(0+offset_x, 118+offset_y);
            break;
        case Zone::GREEN_2:
            lab->setPosition(64+offset_x, 118+offset_y);
            break;
        case Zone::BLUE_3:
            lab->setPosition(128+offset_x, 118+offset_y);
            break;
        case Zone::GREEN_4:
            lab->setPosition(192+offset_x, 118+offset_y);
            break;
        case Zone::BLUE_5:
            lab->setPosition(192+offset_x, 79+offset_y);
            break;
        case Zone::GREEN_6:
            lab->setPosition(192+offset_x, 40+offset_y);
            break;
        case Zone::BLUE_7:
            lab->setPosition(192+offset_x, 0+offset_y);
            break;
        case Zone::GREEN_8:
            lab->setPosition(128+offset_x, 0+offset_y);
            break;
        case Zone::BLUE_9:
            lab->setPosition(64+offset_x, 0+offset_y);
            break;
        case Zone::GREEN_10:
            lab->setPosition(0+offset_x, 0+offset_y);
            break;
        default:
            break;
    }
}

void Align::configDefaultStrategy()
{
    if(selectedColor == BLUE)
    {
        piccolo->setColor(TFT_WHITE,TFT_BLUE);
        grande->setColor(TFT_WHITE,TFT_BLUE);

        if(defaultStrategy == ALPHA_STRATEGY)
        {
            drawPosition(piccolo, Zone::BLUE_1);
            drawPosition(grande, Zone::BLUE_7);

            configuration[0] = Zone::BLUE_1;
            configuration[1] = Zone::BLUE_7;

            Serial.println("1,7");
        }
        else if(defaultStrategy == BETA_STRATEGY)
        {
            drawPosition(piccolo, Zone::BLUE_1);
            drawPosition(grande, Zone::BLUE_5);

            configuration[0] = Zone::BLUE_1;
            configuration[1] = Zone::BLUE_5;

            Serial.println("1,5");
        }
        else if(defaultStrategy == GAMMA_STRATEGY)
        {
            drawPosition(piccolo, Zone::BLUE_1);
            drawPosition(grande, Zone::BLUE_7);

            configuration[0] = Zone::BLUE_1;
            configuration[1] = Zone::BLUE_7;

            Serial.println("1,7");
        }
        else if(defaultStrategy == DELTA_STRATEGY)
        {
            drawPosition(piccolo, Zone::BLUE_3);
            drawPosition(grande, Zone::BLUE_9);

            configuration[0] = Zone::BLUE_3;
            configuration[1] = Zone::BLUE_9;

            Serial.println("3,9");
        }
    }
    else if (selectedColor == GREEN)
    {
        piccolo->setColor(TFT_WHITE, TFT_GREEN);
        grande->setColor(TFT_WHITE, TFT_GREEN);

        if(defaultStrategy == ALPHA_STRATEGY)
        {
            drawPosition(piccolo, Zone::GREEN_10);
            drawPosition(grande,Zone::GREEN_4);

            configuration[0] = Zone::GREEN_10;
            configuration[1] = Zone::GREEN_4;

            Serial.println("10,4");
        }
        else if(defaultStrategy == BETA_STRATEGY)
        {
            drawPosition(piccolo, Zone::GREEN_10);
            drawPosition(grande,Zone::GREEN_8);

            configuration[0] = Zone::GREEN_10;
            configuration[1] = Zone::GREEN_8;

            Serial.println("10,8");
        }
        else if(defaultStrategy == GAMMA_STRATEGY)
        {
            drawPosition(piccolo,Zone::GREEN_10);
            drawPosition(grande,Zone::GREEN_4);

            configuration[0] = Zone::GREEN_10;
            configuration[1] = Zone::GREEN_4;

            Serial.println("10,4");
        }
        else if(defaultStrategy == DELTA_STRATEGY)
        {
            drawPosition(piccolo,Zone::GREEN_6);
            drawPosition(grande,Zone::GREEN_2);

            configuration[0] = Zone::GREEN_6;
            configuration[1] = Zone::GREEN_2;

            Serial.println("6,2");
        }
    }
}

void Align::update()
{
    if(screenChanged)
    {
        set->setToBeUpdate(true);
        alignPiccolo->setToBeUpdate(true);
        alignGrande->setToBeUpdate(true);
        back->setToBeUpdate(true);
        camp->setToBeUpdate(true);
        piccolo->setToBeUpdate(true);
        grande->setToBeUpdate(true);
        slider->setToBeUpdate(true);

        defaultStrategy = View::getCurrentStrategy();
        selectedColor = View::getColor();

        screenChanged = false;
        configDefaultStrategy();
    }

    if(changeDone)
    {
        camp->setToBeUpdate(true);
        piccolo->setToBeUpdate(true);
        grande->setToBeUpdate(true);
        changeDone = false;
    }

    View::update();
}