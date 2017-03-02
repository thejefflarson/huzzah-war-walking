#include "display.hpp"

#define OLED_MOSI   2
#define OLED_CLK   12
#define OLED_DC    13
#define OLED_CS    14
#define OLED_RESET 15
Adafruit_SSD1306 display_(OLED_MOSI, OLED_CLK, OLED_DC, OLED_RESET, OLED_CS);


void clear() {
  display_.clearDisplay();
  display_.setTextColor(WHITE);
  display_.setTextSize(1);
  display_.setCursor(0, 0);
  display_.clearDisplay();
  display_.setCursor(0,0);
}

void show() {
  display_.display();
}

void start_display() {
  Serial.begin(9600);
  display_.begin(SSD1306_SWITCHCAPVCC);
}

Adafruit_SSD1306& display() {
  return display_;
}
