#include "display.hpp"
#include "scanner.hpp"
#include <ESP8266WiFi.h>
#include <memory>


void Scanning::run(Scanner &scanner) {
  int n = WiFi.scanNetworks();
  if(n > 0) {
    for(int i = 0; i < n; i++) {
      if(WiFi.encryptionType(i) == ENC_TYPE_NONE)
        candidates_.push_back(WiFi.SSID(i));
    }
    //scanner.promote(make_unique<>());
  } else {
    //clear();
    //display().println("no networks :(");
    //show();
  }
}

void Sending::run(Scanner& scanner) {

};

void Reporting::run(Scanner& scanner) {
  clear();
  display().println("Yo, try these: ");
  for(auto net : networks_)
    display().println(net);
  show();
};
