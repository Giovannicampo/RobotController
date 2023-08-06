#include "enable.h"
#include <cmath>
#include "sharedDefines.h"

Enable::Enable()
    : View(ENABLE_VIEW)
{
    screenChanged = false;
    game_ended = 0;
    showXPos = false;
    score = 0;
    num_palline = 0;
    posPiccolo = new int[2];
    posGrande = new int[2];
    for(uint8_t i=0; i<2; i++)
    {
        posPiccolo[i] = -1;
        posGrande[i] = -1;
    }

    initWidgets();

    enable->setOnClick(([this]() {
        toggle_led();
        setEnable();
        View::setTxFlag(ENABLE_TX);
    }));   

    back->setOnClick(([this]() {
        setBack();
    }));
}

void Enable::initWidgets()
{
    // enable button
    enable = new Button(20,20,100,50, TFT_YELLOW, 3, TFT_ORANGE, TFT_WHITE, ENABLE_BUTTON, 2, false);

    // labels
    strategy = new Label(20, 80, TFT_WHITE, bgColor, 2, View::getCurrentStrategy());
    color = new Label(20, 98, View::getColor() == BLUE ? TFT_BLUE : TFT_GREEN, bgColor, 2, View::getColor());
    configuration = new Label(20, 116, TFT_ORANGE, bgColor, 2, "Config: " + getConf());

    totScore = new Label(100, 200, TFT_WHITE, bgColor, 2, "Score: ");
    totScore->hide();

    scoreBasket = new Label(225,140, TFT_ORANGE, bgColor, 3, "SCOREBASKET"); // da gestire

    // camp hidden in costruzione
    camp = new Camp(0,0);
    camp->hide();

    // XPos
    grande = new XPos(0,130, TFT_RED);
    piccolo = new XPos(0,130, TFT_YELLOW);
    grande->hide();
    piccolo->hide();

    // picture
    logo = new Picture(225,170,unict_team_logo,50,49,TFT_WHITE);
    basket = new Picture(190,50,bmp_basket,110,80,TFT_WHITE);

    // backbutton
    back = new BackButton(80, 170, TFT_WHITE);

    addWidget(enable);
    addWidget(strategy);
    addWidget(color);
    addWidget(configuration);
    addWidget(basket);
    addWidget(scoreBasket);
    addWidget(camp);
    addWidget(logo);
    addWidget(back);
    addWidget(piccolo);
    addWidget(grande);
    addWidget(totScore);
}

void Enable::setBack()
{
    if(showXPos)
    {
        View::clearScreen();

        camp->hide();
        piccolo->hide();
        grande->hide();
        totScore->hide();

        enable->show();
        strategy->show();
        color->show();
        configuration->show();
        logo->show();

        scoreBasket->setPosition(225,140);
        basket->setPosition(190,50);
        back->setPosition(80,170);

        showXPos = false;
    }
    this->display->changeView(PRINCIPALE_VIEW);
    setScreenChanged(true);
}

void Enable::setEnable()
{
    int* config = View::getConfiguration();
    // if(config[0] == -1 || config[1] == -1){
    //     View::setEnabled(false);
    //     return;
    // }
    View::setEnabled(true);
    View::clearScreen();
    camp->show();
    grande->show();
    piccolo->show();
    totScore->show();

    totScore->setToBeUpdate(true);
    scoreBasket->setToBeUpdate(true);
    scoreBasket->setPosition(255,140);
    basket->setToBeUpdate(true);
    basket->setPosition(220,50);
    back->setToBeUpdate(true);
    back->setPosition(60,200);

    enable->hide();
    strategy->hide();
    color->hide();
    configuration->hide();
    logo->hide();
    showXPos = true;
}

void Enable::setScreenChanged(bool state)
{
    screenChanged = state;
}

void Enable::setGameEnded()
{
    t_can_score_data score = View::getScoreGrande();
    bool ge = (score.flags & FLAGS_GAME_END_MASK) != 0;
    // Serial.printf("[Enable]%s\n", !ge ? "game is not ended yet" : "game has just ended");
    if(ge && game_ended == 0){
        game_ended = (unsigned char)ge;
    }
}

void Enable::setStrategyLabel()
{
    const String stgy = View::getCurrentStrategy();
    if(stgy != "") {strategy->setText(stgy);}
}

void Enable::setColorLabel()
{
    const String col = View::getColor();
    if (col != "") 
    {
        color->setText(col); 
        color->setColor(View::getColor() == BLUE ? TFT_BLUE : TFT_GREEN, bgColor);
    }
}

void Enable::setConfigLabel()
{
    configuration->setText("CONFIG " + getConf());
}

void Enable::setBasketScore()
{
    char s[80];
    num_palline = View::getNumPalline();
    // printf("[Enable] Palline: %d\n", num_palline);
    sprintf(s,"%3d",num_palline);
    scoreBasket->setToBeUpdate(true);
    scoreBasket->setText(s);
}

void Enable::setPosition()
{
    // in mancanza di dati in ricezione per testare
    t_can_robot_position posCanGrande = View::getTCanRobotPositionGrande();
    t_can_robot_position posCanPiccolo = View::getTCanRobotPositionPiccolo();

    if(abs(posGrande[0] - posCanGrande.x) > 100 || abs(posGrande[1] - posCanGrande.y) > 100 || 
    abs(posPiccolo[0] - posCanPiccolo.x) > 100 || abs(posPiccolo[1] - posCanPiccolo.y) > 100){
        camp->setToBeUpdate(true);

        posGrande[0] = posCanGrande.x; // x grande
        posGrande[1] = posCanGrande.y; // y grande

        posPiccolo[0] = posCanPiccolo.x; // x piccolo
        posPiccolo[1] = posCanPiccolo.y; // y piccolo
    }
}

void Enable::setTotScore()
{
    char s[80];
    t_can_score_data score_p = View::getScorePiccolo();
    t_can_score_data score_g = View::getScoreGrande();
    int _palline = View::getNumPalline();
    // Serial.printf("[Enable] score piccolo: %d\n", score_p.score);
    // Serial.printf("[Enable] score grande: %d\n", score_g.score);
    bool small_in_home = (score_p.flags & FLAGS_ROBOT_IN_HOME) != 0;
    bool big_in_home = (score_g.flags & FLAGS_ROBOT_IN_HOME) != 0;
    uint16_t total =(uint16_t)(score_p.score + score_g.score + _palline + 5);
    if (small_in_home && big_in_home)
        total += 15;
    if (big_in_home)
        total += 5; // funny action
    // Serial.printf("[Enable] Total score: %d\n", total);
    sprintf(s,"Score:    %d       ", total);
    totScore->setToBeUpdate(true);
    totScore->setText(s);
}

void Enable::setXPos()
{
    // normalizzazione da 2000x3000 a 150x225
    int x_pic = (int)(posPiccolo[0]*225)/3000;
    int y_pic = (int)130-(posPiccolo[1]*150)/2000;
    int x_gra = (int)(posGrande[0]*225)/3000;
    int y_gra = (int)130-(posGrande[1]*150)/2000;

    piccolo->setX(x_pic);
    piccolo->setY(y_pic);
    grande->setX(x_gra);
    grande->setY(y_gra);
}

String Enable::getConf() {
    const int *const int_conf = View::getConfiguration();
    String conf;
    conf += int_conf[0];
    conf += int_conf[1];
    return conf;
}

void Enable::update()
{
    if(screenChanged)
    {
        enable->setToBeUpdate(true);
        strategy->setToBeUpdate(true);
        color->setToBeUpdate(true);
        configuration->setToBeUpdate(true);
        camp->setToBeUpdate(true);
        basket->setToBeUpdate(true);
        scoreBasket->setToBeUpdate(true);
        logo->setToBeUpdate(true);
        back->setToBeUpdate(true);

        setStrategyLabel();
        setColorLabel();
        setConfigLabel();

        screenChanged = false;
    }

    if(showXPos)
    {
        piccolo->setToBeUpdate(true);
        grande->setToBeUpdate(true);
        setPosition();
        setXPos();
        
    }
    
    // solo per test
    if(game_ended == 0)
    {
        setGameEnded();
        setBasketScore();
    }

    setTotScore();

    View::update();
}
