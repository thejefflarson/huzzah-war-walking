#include <Arduino.h>

#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <ESP8266WiFi.h>

// If using software SPI (the default case):
#define OLED_MOSI   2
#define OLED_CLK   12
#define OLED_DC    13
#define OLED_CS    14
#define OLED_RESET 15
Adafruit_SSD1306 display(OLED_MOSI, OLED_CLK, OLED_DC, OLED_RESET, OLED_CS);



void setup() {
  Serial.begin(9600);
  display.begin(SSD1306_SWITCHCAPVCC);
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0,0);
  display.println("Hi Jeff, looking for open wifi networks.");
  display.display();
}

void loop() {
  int n = WiFi.scanNetworks();
  display.clearDisplay();
  display.setCursor(0,0);
  if(n > 0) {
    display.println("Yo, try these:");
    for(int i = 0; i < n; i++){
      display.println(WiFi.SSID(i));
    }
  } else {
    display.println("no networks :(");
  }
  display.display();
  delay(10);
}
