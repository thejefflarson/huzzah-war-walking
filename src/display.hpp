#ifndef SRC_DISPLAY
#define SRC_DISPLAY
#include <Arduino.h>
#include <Adafruit_SSD1306.h>

void show();
void clear();
void start_display();
Adafruit_SSD1306 & display();

#endif
