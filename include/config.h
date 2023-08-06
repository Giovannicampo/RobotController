/*Core libraries*/
#include <SPI.h>
#include <SPIFFS.h>

#include "mrf24j.h"


/* DISPLAY AND TOUCH PINS */
#undef TFT_MISO
#undef TFT_MOSI
#undef TFT_SCLK
#undef TFT_CS
#undef TFT_DC
#undef TFT_RST
#undef TOUCH_CS

#define TFT_MISO 12
#define TFT_MOSI 13
#define TFT_SCLK 14
#define TFT_CS   15  // Chip select control pin
#define TFT_DC   2   // Data Command control pin
#define TFT_RST  4   // Reset pin (could connect to RST pin)
#define TOUCH_CS 27  // Chip select pin (T_CS) of touch screen

/* RADIO PINS */

#define RADIO_MISO    26
#define RADIO_MOSI    32
#define RADIO_SCLK    18
#define RADIO_CS      23
#define RADIO_INT     22
#define RADIO_WAKEUP  21
#define RADIO_RST     19

/* HX711 circuit wiring */

#define LOADCELL_DOUT_PIN 17
#define LOADCELL_SCK_PIN 16