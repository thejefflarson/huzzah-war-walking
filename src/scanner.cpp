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
    scanner.promote(make_unique<Sending>(candidates_));
  } else {
    scanner.promote(make_unique<Failing>("no networks :("));
  }
}

void Sending::run(Scanner& scanner) {
  auto candidate = candidates_.back();
  candidates_.pop_back();
  WiFi.begin(candidate.c_str(), "");
  int16_t timeout = 5000;
  while(timeout > 0 && WiFi.status() != WL_CONNECTED) {
    time_t now = time(NULL);

  };
};

void Recieving::run(Scanner& scanner) {

};

void Failing::run(Scanner& scanner) {
  clear();
  display().println(message_);
  show();
  scanner.promote(make_unique<Scanning>());
};

void Reporting::run(Scanner& scanner) {
  clear();
  display().println("Yo, try: ");
  display().println(network_);
  sleep(60);
  show();
};
