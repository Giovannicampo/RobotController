#ifndef __SHAREDDEFINES_H
#define __SHAREDDEFINES_H

#define BLUE "blue"
#define GREEN "green"

#define PRINCIPALE_VIEW "principale"
#define STRATEGY_VIEW "stgy"
#define ALIGN_VIEW "align"
#define ENABLE_VIEW "enable"

#define ALPHA_STRATEGY "ALPHA"
#define BETA_STRATEGY "BETA"
#define GAMMA_STRATEGY "GAMMA"
#define DELTA_STRATEGY "DELTA"

#define ENABLE_BUTTON "ENABLE"

#define GREEN_LED 33

enum LedState : short int
{
  ON = 1,
  OFF = 0,
  IDLE = -1
};

extern LedState _led_state;

inline void toggle_led(){
  _led_state = LedState::ON;
}

enum Zone : short int
{
  BLUE_1 = 1,
  GREEN_2,
  BLUE_3,
  GREEN_4,
  BLUE_5,
  GREEN_6,
  BLUE_7,
  GREEN_8,
  BLUE_9,
  GREEN_10,
};

#endif
