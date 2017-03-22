#ifndef SRC_SCANNER
#define SRC_SCANNER

#include <Arduino.h>

#include <memory>
#include <vector>

// PlatformIO doesn't support c++14 yet
template<typename T, typename... Args>
std::unique_ptr<T> make_unique(Args&&... args){
  return std::unique_ptr<T>(new T(std::forward<Args>(args)...));
}

class State;
class Scanner {
public:
  Scanner();
  void tick();
  void promote(std::unique_ptr<State> state);
private:
  std::unique_ptr<State> state_;
};

class State {
public:
  virtual void run(Scanner& scanner) = 0;
  virtual ~State() = default;
};

class Scanning : public State {
public:
  Scanning() : candidates_() {}
  void run(Scanner& scanner);
private:
  std::vector<String> candidates_;
};

class Sending : public State {
  Sending(std::vector<String> candidates) :
    candidates_(candidates) {};
  void run(Scanner& scanner);
private:
  std::vector<String> candidates_;
};

class Connecting : public State {
public:
  Connecting(std::vector<String> candidates) :
    candidates_(candidates),
    connecting_(false),
    started_(millis()) {
    current_ = candidates_.back();
    candidates.pop_back();
  }
  void run(Scanner& scanner);
private:
  bool connecting_;
  std::vector<String> candidates_;
  String current_;
  unsigned long started_;
};

class Recieving : public State {
public:
  Recieving(String current, std::vector<String> candidates) :
    current_(current),
    candidates_(candidates) {}
  void run(Scanner& scanner);
private:
  std::vector<String> candidates_;
  String current_;
};

class Reporting : public State {
public:
  Reporting(String network) :
    network_(network),
    started_(millis()) {}
  void run(Scanner& scanner);
private:
  String network_;
  unsigned long started_;
};

class Failing : public State {
public:
  Failing(String message, std::unique_ptr<State> next) :
    message_(message),
    next_(std::move(next)),
    started_(millis()) {}
  void run(Scanner& scanner);
private:
  String message_;
  std::unique_ptr<State> next_;
  unsigned long started_;
};

#endif
