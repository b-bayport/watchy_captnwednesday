#ifndef MAIN_H
#define MAIN_H

#include <Watchy.h>
#include "captnwednesday_img.h"
#include "icons.h"
#include "fonts/Tintin_Dialogue8pt7b.h"
#include "fonts/Tintin_Dialogue9pt7b.h"
#include "fonts/Tintin_Dialogue10pt7b.h"
#include "fonts/Tintin_Dialogue16pt7b.h"

RTC_DATA_ATTR bool light = true;
RTC_DATA_ATTR int face = 0;

const uint8_t BATTERY_SEGMENT_WIDTH = 7;
const uint8_t BATTERY_SEGMENT_HEIGHT = 11;
const uint8_t BATTERY_SEGMENT_SPACING = 9;
const uint8_t WEATHER_ICON_WIDTH = 48;
const uint8_t WEATHER_ICON_HEIGHT = 32;

class WatchyMoto : public Watchy {
  using Watchy::Watchy;
  public:
    void drawWatchFace();
    void drawWrapText(String text);
    void drawBattery();
    void drawSteps();
    void drawCaptnWednesday(bool light, float batt);
    virtual void handleButtonPress(); //Must also be virtual in Watchy.h
};

#include "captnwednesday.h"
//#include "faceXXXX.h"


void WatchyMoto::handleButtonPress() {
  if (guiState == WATCHFACE_STATE) {
    //Up and Down switches 
    uint64_t wakeupBit = esp_sleep_get_ext1_wakeup_status();
    if (wakeupBit & UP_BTN_MASK) {
      face--;
      if (face < 0) {face = 0; } //update face=X based on face qty
        RTC.read(currentTime);
        showWatchFace(true);
        return;
    }
    if (wakeupBit & DOWN_BTN_MASK) {
      face++;
      if (face > 0) {face = 0;} // update face > X  based on face qty
      RTC.read(currentTime);
      showWatchFace(true);
      return;
    }
    if (wakeupBit & BACK_BTN_MASK) {
      light = !light;
      RTC.read(currentTime);
      showWatchFace(true);
      return;
    }
    if (wakeupBit & MENU_BTN_MASK) {
      Watchy::handleButtonPress();
      return;
    }
  } else {Watchy::handleButtonPress();}
  return;
}


void WatchyMoto::drawWatchFace() {
  // ** UPDATE **
  // resets step counter at midnight daily
  if (currentTime.Hour == 00 && currentTime.Minute == 00) {
    sensor.resetStepCounter();
  }

  // ** GET BATTERY **
  float batt = (getBatteryVoltage()-3.3);
  if (batt > 1) { batt = 1; } else if (batt < 0) { batt = 0; }

  // ** DRAW WATCHFACE **
  if (face == 0) {
    drawCaptnWednesday(light, batt);
  }
  /*if (face == 1) {
    drawFaceXXXX(light, batt);
  }*/
}




#endif