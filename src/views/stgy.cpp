#include "stgy.h"
#include "sharedDefines.h"

Stgy::Stgy()
    : View(STRATEGY_VIEW)
{
    screenChanged = false;

    // buttons
    alpha = new Button(12, 12, 100, 50,TFT_YELLOW, 3, TFT_ORANGE, TFT_WHITE, ALPHA_STRATEGY, 2, false);
    beta = new Button(12, 67, 100, 50,TFT_YELLOW, 3, TFT_ORANGE, TFT_WHITE, BETA_STRATEGY, 2, false);
    gamma = new Button(12, 122, 100, 50,TFT_YELLOW, 3, TFT_ORANGE, TFT_WHITE, GAMMA_STRATEGY, 2, false);
    delta = new Button(12, 177, 100, 50,TFT_YELLOW, 3, TFT_ORANGE, TFT_WHITE, DELTA_STRATEGY, 2, false);

    // //picture
    cake = new Picture(202, 0, cake_bitmap, 103, 100, TFT_WHITE);

    back = new BackButton(277, 202, TFT_WHITE);

    //labels
    strategy = new Label(212, 122, TFT_ORANGE, bgColor, 3, "");

    addWidget(alpha);
    addWidget(beta);
    addWidget(gamma);
    addWidget(delta);
    addWidget(back);
    addWidget(cake);

    addWidget(strategy);

    alpha->setOnClick(([this]() {
        toggle_led();
        setStrategy(ALPHA_STRATEGY);
    }));

    beta->setOnClick(([this]() {
        toggle_led();
        setStrategy(BETA_STRATEGY);
    }));

    gamma->setOnClick(([this]() {
        toggle_led();
        setStrategy(GAMMA_STRATEGY);
    }));

    delta->setOnClick(([this]() {
        toggle_led();
        setStrategy(DELTA_STRATEGY);
    }));

    back->setOnClick(([this]() {
        this->display->changeView(PRINCIPALE_VIEW);
        setScreenChanged(true);
    }));
}

void Stgy::setScreenChanged(bool state)
{
    screenChanged = state;
}

void Stgy::update()
{
    if(screenChanged)
    {
        alpha->setToBeUpdate(true);
        beta->setToBeUpdate(true);
        delta->setToBeUpdate(true);
        gamma->setToBeUpdate(true);
        back->setToBeUpdate(true);
        cake->setToBeUpdate(true);
        
        screenChanged = false;
    }
    View::update();
}

void Stgy::setStrategy(String stgy)
{
    Serial.println("Strategy selected "+ stgy);

    // in stgy
    strategy->setText(stgy);
    strategy->setToBeUpdate(true);

    View::setCurrentStrategy(stgy);
}
