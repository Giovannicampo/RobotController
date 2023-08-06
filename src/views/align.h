#ifndef ALIGN_H
#define ALIGN_H

#include <string>
#include "view.h"
#include "widgets/button.h"
#include "widgets/backbutton.h"
#include "widgets/label.h"
#include "widgets/camp.h"
#include "widgets/slider.h"

enum Setting : short int
{
    GRANDE,
    PICCOLO,
};

class Align : public View
{
    private:
        Button* set;
        Button* alignPiccolo;
        Button* alignGrande;
        BackButton* back;
        Camp* camp;
        Label* grande;
        Label* piccolo;
        Slider* slider;

        Setting selectedSetting;
        bool changeDone;
        bool screenChanged;

        String defaultStrategy;
        String selectedColor;
        int* configuration;
    public:
    Align();

    void setScreenChanged(bool state);
    void drawPosition(Label* lab, int zona);
    void configDefaultStrategy();
    void setSetting(Setting state);
    void setPositionStrategy(int index);

    //Override da View
    void update();
};

#endif