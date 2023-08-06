#include "bilancia.h"

Bilancia::Bilancia(HX711* scale, Display* display)
{
    this->_scale = scale;
    this->_display = display;
}

long Bilancia::read_scale()
{
    if (_scale->is_ready()) {
      long reading = _scale->read();
      // Serial.println(reading);
      return reading;
    }

    return -1;
}


void Bilancia::do_zero()
{
  long sum = 0;
  Serial.println("Doing zero...");
  for (int i = 0; i < MAX_ZERO;i++) {
    long data = read_scale();
    if (data > 0)
      sum += data;
    else
      i--;
    delay(1);
  }
  _zero = sum / MAX_ZERO;
}

int Bilancia::do_scale()
{
    int balls_estimate = -1;
    long data = read_scale();
    if (data > 0) {
      data = data - _zero;
      float balls_low = data / 6500.0;
      float balls_high = data / 7500.0;
      balls_estimate = (int)(balls_high + 0.5);
      // Serial.print("Scale reading: ");
      // Serial.print(data);
      // Serial.print("   - Balls: ");
      // Serial.print(balls_low);
      // Serial.print("  ");
      // Serial.print(balls_high);
      // Serial.print("  ");
      // Serial.println(balls_estimate);
    }
    return balls_estimate;
}

void Bilancia::update()
{
    int num = do_scale();
    if(num != -1){
    _display->onBilanciaReceive(num);
    }
    delay(1);
}