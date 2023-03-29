#include <Arduino.h>
#include <TFT_eSPI_ext.h>
#include "HX711.h"
#include "display.h"
#include "views/principale.h"
#include "ArrayList.h"

TFT_eSPI tft = TFT_eSPI();

// è stata configurata solo la schermata principale
View* views[1] = {new Principale()};
Display* display = new Display(&tft, views, 1);


void setup()
{
    Serial.begin(115200);
    tft.init();
    uint16_t calData[5] = { 389, 3511, 291, 3456, 7 };
    tft.setTouch(calData);

    tft.fillScreen(TFT_BLACK);

// calibration data for touch

}

void loop()
{
    // entry point
    display->update();
}