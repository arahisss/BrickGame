#ifndef SNAKE_CONTROLLER
#define SNAKE_CONTROLLER

#include <chrono>
#include <thread>

#include "SnakeModel.h"

class Timer {
 public:
  using Clock = std::chrono::steady_clock;
  using TimePoint = std::chrono::time_point<Clock>;
  using Duration = std::chrono::milliseconds;
  Timer(int interval_ms) : interval(interval_ms), lastTick(Clock::now()) {};

  bool tick() {
    auto now = Clock::now();
    if (std::chrono::duration_cast<Duration>(now - lastTick) >= interval) {
      lastTick = now;
      return true;
    }
    return false;
  }

  void setInterval(int interval_ms) { interval = Duration(interval_ms); }

  void reset() {
    lastTick = Clock::now();  // Сброс таймера
  }

 private:
  Duration interval;
  TimePoint lastTick;
};
enum class State { START, GAME, EATING, PAUSE, GAME_OVER };

class SnakeController {
 private:
  SnakeModel* model;
  bool instantMove = false;
  Timer timer;
  int speed = 800;
  State state = State::GAME;

 public:
  SnakeController(SnakeModel* m) : model(m), timer(550) {};
  ~SnakeController();
  State getState();
  int getSpeed();
  GameInfo_t getGameInfo();
  void userInput(UserAction_t user_action, bool hold);
  void handleGame();
  void handlePause();
  void handleEating();
  void updateSpeed();
  void handleGameOver();
  void turnSnake(UserAction_t user_action);
  void updateGameState();
  Direction toDirection(UserAction_t user_action);
};

#endif