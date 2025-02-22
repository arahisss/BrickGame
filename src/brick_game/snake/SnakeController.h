#ifndef SNAKE_CONTROLLER
#define SNAKE_CONTROLLER

#include <chrono>
#include <thread>

#include "SnakeModel.h"

namespace s21 {
class Timer {
 public:
  using Clock = std::chrono::steady_clock;
  using TimePoint = std::chrono::time_point<Clock>;
  using Duration = std::chrono::milliseconds;
  Timer(int interval_ms) : interval(interval_ms), lastTick(Clock::now()){};

  virtual bool tick() {
    auto now = Clock::now();
    if (std::chrono::duration_cast<Duration>(now - lastTick) >= interval) {
      lastTick = now;
      return true;
    }
    return false;
  }

  virtual void setInterval(int interval_ms) {
    interval = Duration(interval_ms);
  }

  virtual void reset() { lastTick = Clock::now(); }

 private:
  Duration interval;
  TimePoint lastTick;
};
enum class State { START, GAME, EATING, PAUSE, GAME_OVER };
/**
 * @class SnakeController
 * @brief Контроллер для игры "Змейка".
 *
 * Класс SnakeController отвечает за управление логикой игры "Змейка".
 * Он взаимодействует с моделью (SnakeModel) для обновления состояния игры
 * и обработки пользовательского ввода. Контроллер также управляет таймером
 * и скоростью игры.
 * @param model Указатель на объект модели SnakeModel.
 * @param instantMove Флаг для мгновенного перемещения
 * @param timer Таймер игры
 * @param state Состояние КА игры
 * @param speed скорость
 *
 */
class SnakeController {
 private:
  SnakeModel* model;
  bool instantMove = false;
  Timer timer;
  int speed = 800;
  State state = State::START;

 public:
  SnakeController(SnakeModel* m) : model(m), timer(550){};
  ~SnakeController();
  State getState();
  void setState(State new_state);
  void setInstantMove(bool newInstantMove);
  bool getInstantMove();
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
}  // namespace s21
#endif