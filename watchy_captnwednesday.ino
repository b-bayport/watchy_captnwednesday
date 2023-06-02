#include "main.h"
#include "settings.h"

WatchyMoto watchy(settings);

void setup() {
//  for Screenshot of watchface output to serial port, reference instructions at https://github.com/sqfmi/Watchy/wiki/Screenshots-of-Watchfaces
//  Serial.begin(115200);
//  while (!Serial); // wait for serial port to connect. Needed for native USB port on Arduino only
  watchy.init();

  }

void loop() {}
