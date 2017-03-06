#include "display.hpp"
#include "scanner.hpp"
#include <ESP8266WiFi.h>
#include <memory>

Scanner::Scanner() {
  state_ = make_unique<Scanning>();
}

void Scanner::tick() {
  state_->run(*this);
}

void Scanner::promote(std::unique_ptr<State> state) {
  state_ = std::move(state);
};


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
