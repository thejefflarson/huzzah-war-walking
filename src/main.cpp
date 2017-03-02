#include <Arduino.h>
#include "display.hpp"
#include "scanner.hpp"

void setup() {
  start_display();
  clear();
  display().println("Hi Jeff, looking for open wifi networks.");
  show();
}

auto scanner = Scanner();

void loop() {
  scanner.tick();
}
