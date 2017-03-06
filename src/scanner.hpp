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
public:
  Sending() {}
  void run(Scanner& scanner);
};

class Recieving : public State {
public:
  Recieving() {}
  void run(Scanner& scanner);
};

class Reporting : public State {
public:
  Reporting(std::vector<String> networks) :
    networks_(networks) {}
  void run(Scanner& scanner);
private:
  std::vector<String> networks_;
};

#endif
