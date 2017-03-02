#ifndef SRC_SCANNER
#define SRC_SCANNER

#include <memory>
#include <string>
#include <vector>


// PlatformIO doesn't support c++14 yet
template<typename T, typename... Args>
std::unique_ptr<T> make_unique(Args&&... args){
  return std::unique_ptr<T>(new T(std::forward<Args>(args)...));
}


class Scanner;
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
  std::vector<std::string> candidates_;
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
  Reporting(std::vector<std::string> networks) :
    networks_(networks) {}
  void run(Scanner &scanner);
private:
  std::vector<std::string> networks_;
};

class Scanner {
public:
  Scanner() : state_(make_unique<Scanning>()) {}
  void tick() {
    state_->run(*this);
  };

  void promote(std::unique_ptr<State> state) {
    state_ = std::move(state);
  };
private:
  std::unique_ptr<State> state_;
};


#endif
