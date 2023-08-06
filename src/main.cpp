#include <Arduino.h>
#include <TFT_eSPI_ext.h>
#include "mrf24j.h"
#include "HX711.h"
#include "display.h"
#include <config.h>
#include "bilancia.h"
#include "controller.h"
#include "views/principale.h"
#include "views/stgy.h"
#include "views/align.h"
#include "views/enable.h"
#include "widgets/unict_team_logo.h"
#include "ArrayList.h"

Mrf24j * mrf;
HX711 scale;
TFT_eSPI tft = TFT_eSPI();
uint8_t data[12] = {0};

SPIClass radio_spi(HSPI);

// è stata configurata solo la schermata principale
View* views[4] = {new Align(), new Enable(), new Stgy(), new Principale()};

Display* display = new Display(&tft, views, 4);
Bilancia* bilancia = new Bilancia(&scale, display);
Controller* controller = new Controller(mrf, display);

/* defining functions*/
void interrupt_routine();
void handle_rx(){controller->handleRx();}
void handle_tx(){controller->handleTx();}

/* config bilancia */
void config_bilancia(){
  scale.begin(LOADCELL_DOUT_PIN, LOADCELL_SCK_PIN);
  bilancia->do_zero();
}

/* timer led */
hw_timer_t *_timer_led = NULL;
LedState _led_state = LedState::IDLE;

void IRAM_ATTR onTimer(){
  switch(_led_state)
  {
    case LedState::ON:
      digitalWrite(GREEN_LED, 1);
      _led_state = LedState::OFF;
      break;
    case LedState::OFF:
      digitalWrite(GREEN_LED, 0);
      _led_state = LedState::IDLE;
      break;
  }
}

void transmission()
{
  if(controller->onTrasmission() != nullptr)
  {
    delay(1);
    uint8_t* result = controller->onTrasmission();
    data[0] = 0x10;
    data[1] = 0x07;
    for(uint8_t i=2; i<12; i++)
    {
      data[i] = result[i-2];
    }
    Serial.printf("data is %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d\n", data[0], data[1], data[2], data[3], data[4], data[5], data[6], data[7], data[8], data[9], data[10], data[11]);
    mrf->send16(0xFFFF,data, 12); // da provare
    display->setTxFlag(false);
    Serial.printf("data correctly sent\n");
    delay(2000);
  }
}


void interrupt_routine() {
  mrf->interrupt_handler(); // mrf24 object interrupt routine
}

void setup()
{
    pinMode(GREEN_LED, OUTPUT);
    digitalWrite(GREEN_LED, 0);

    /* psc -> 8000 autoreload -> 3000 granularity of 300 ms*/
    _timer_led = timerBegin(0, 8000, true);
    timerAttachInterrupt(_timer_led, &onTimer, true);
    timerAlarmWrite(_timer_led, 3000, true);
    timerAlarmEnable(_timer_led);

    Serial.begin(115200);
    tft.init();
    uint16_t calData[5] = { 389, 3511, 291, 3456, 7 };
    tft.setTouch(calData);

    tft.setRotation(1);
    tft.fillScreen(TFT_BLACK);
    tft.setTextColor(TFT_WHITE);
    tft.setTextSize(2);
    tft.setCursor(110,100);
    tft.print("Loading...");
    tft.drawBitmap(140,150,unict_team_logo,50,49,TFT_WHITE);

    Serial.println("Setting up the radio 802.15.4");
    radio_spi.setBitOrder(MSBFIRST);
    radio_spi.setDataMode(SPI_MODE0);
    radio_spi.begin(RADIO_SCLK, RADIO_MISO, RADIO_MOSI, -1);
    mrf = new Mrf24j(RADIO_RST, RADIO_CS, RADIO_INT, RADIO_WAKEUP, &radio_spi);
    mrf->reset();
    mrf->init();
    mrf->set_pan(0xa570);
    mrf->address16_write(0x8931);
    mrf->set_channel(24);
    mrf->set_promiscuous(true);
    mrf->set_bufferPHY(true);
    attachInterrupt(RADIO_INT, interrupt_routine, CHANGE);
    Serial.println("Radio is ready!");

    tft.setCursor(80,115);
    tft.print("Setting scale...");
    config_bilancia();

    tft.fillScreen(TFT_BLACK);
}

void loop()
{
    // entry point
    display->update();
    bilancia->update();
    transmission(); 
    mrf->check_flags(&handle_rx, &handle_tx);
}