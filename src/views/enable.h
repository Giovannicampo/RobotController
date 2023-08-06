#ifndef ENABLE_H
#define ENABLE_H

#include "view.h"
#include "widgets/button.h"
#include "widgets/label.h"
#include "widgets/backbutton.h"
#include "widgets/camp.h"
#include "widgets/picture.h"
#include "widgets/unict_team_logo.h"
#include "widgets/basket.h"
#include "widgets/xpos.h"

class Enable : public View
{
    private:
        Button* enable;

        // show per costruzione, hide dopo enable Button
        Label* strategy;
        Label* color;
        Label* configuration;
        Label* totScore;

        // hide per costruzione, show dopo enable Button
        Camp* camp;

        // oggetti g_position e p_position da posizionare nel campo
        XPos* grande;
        XPos* piccolo;

        // da aggiungere picture del cestino
        Picture* basket;
        Label* scoreBasket;

        Picture* logo;

        BackButton* back;

        bool screenChanged;
        unsigned char game_ended;

        void initWidgets();
        String getConf();
        void setEnable();
        void setBack();

        int* posPiccolo;
        int* posGrande;
        int num_palline;
        int score;

        bool showXPos;

    public:
        Enable();

        //Override da View
        void setScreenChanged(bool state);
        void setGameEnded();

        void setStrategyLabel();
        void setColorLabel();
        void setConfigLabel();

        void update();

        // solo per testare

        // solo per testare
        void setTotScore();
        void setPosition();
        void setBasketScore();
        
        void setXPos();
};

#endif