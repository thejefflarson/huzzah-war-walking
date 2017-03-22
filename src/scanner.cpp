#include "display.hpp"
#include "scanner.hpp"
#include "tweetnacl.h"
#include <ESP8266WiFi.h>
#include <memory>

void randombytes(uint8_t *x, uint32_t xlen) {
  if(os_get_random(x, xlen) == -1) abort(); // no messing about here
}

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
    scanner.promote(make_unique<Sending>(candidates_));
  } else {
    scanner.promote(make_unique<Failing>("no networks :("));
  }
}

void Connecting::run(Scanner& scanner) {
  if(!connecting_) {
    WiFi.begin(current_.c_str(), "");
    started_ = millis();
  } else {
    if((millis() - started_) < 5000) {
      if(WiFi.status() == WL_CONNECTED)
        scanner.promote(make_unique<Sending>(candidates_, current_));
    } else {
      auto next = new Failing("Could not connect to",
                            make_unique<Sending>(candidates_));
      return scanner.promote(std::unique_ptr<State>(next));
    }
  }
};

void Sending::run(Scanner& scanner) {

};

void Recieving::run(Scanner& scanner) {

};

void Failing::run(Scanner& scanner) {
  if(millis() - started_ < 1000) {
    clear();
    display().println(message_);
    show();
  } else {
    scanner.promote(std::move(next_));
  }
};

void Reporting::run(Scanner& scanner) {
  if(millis() - started_ < 60000) {
    clear();
    display().println("Yo, try: ");
    display().println(network_);
    show();
  } else {
    scanner.promote(make_unique<Scanning>());
  }
};
