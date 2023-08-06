#ifndef VIEW_H
#define VIEW_H

#include <Arduino.h>
#include <widget.h>
#include <TFT_eSPI.h>
#include <ArrayList.h>
#include <zigbee_frames.h>
#include "display.h"

class Display;

class View 
{
    String name;
    ArrayList<Widget*> widgets;
    TFT_eSPI* tft;
    uint id_widget = 0x00;

    protected:
        Display* display;
        uint16_t bgColor = TFT_BLACK;

    public:
        View(String name);
        String getName();
        void addWidget(Widget* widget);
        void removeWidget(Widget* widget);
        virtual void update();
        void setTFT(TFT_eSPI* tft);
        TFT_eSPI* getTFT();
        void setDisplay(Display* display);
        void clearScreen();

        //trasmissione align e enable
        static t_can_strategy_command* packAlign(uint8_t index);
        static uint8_t* txAlignGrande();
        static uint8_t* txAlignPiccolo();
        static uint8_t* txEnable();
        static uint8_t tx_flag;
        static void setTxFlag(uint8_t flag);


        // info da trasmettere
        static String _strategy;
        static String _color;
        static int* _configuration;
        static bool _enabled;

        static void setCurrentStrategy(String stgy);
        static String getCurrentStrategy();
        static void setColor(String color);
        static String getColor();
        static void setConfiguration(int* config);
        static int* getConfiguration();
        static void setEnabled(bool state);
        static bool getEnabled();

        // info da ricevere
        static t_can_robot_position positionPiccolo;
        static t_can_robot_position positionGrande;
        static t_can_robot_battery batteryPiccolo;
        static t_can_score_data score_piccolo;
        static t_can_score_data score_grande;
        static int numPalline;
        
        static void setTCanRobotPosition(t_can_robot_position pos, uint8_t index);
        static t_can_robot_position getTCanRobotPositionPiccolo();
        static t_can_robot_position getTCanRobotPositionGrande();

        static void setTCanRobotBattery(t_can_robot_battery bat);
        static t_can_robot_battery getTCanRobotBatteryPiccolo();

        static void setScorePiccolo(t_can_score_data s);
        static t_can_score_data getScorePiccolo();

        static void setScoreGrande(t_can_score_data s);
        static t_can_score_data getScoreGrande();

        static void setNumPalline(int num);
        static int getNumPalline();
        
        virtual void setScreenChanged(bool state) = 0;
};

#endif