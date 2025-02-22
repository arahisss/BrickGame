#include "SnakeController.h"

namespace s21 {
SnakeController::~SnakeController() {}

State SnakeController::getState() { return state; }
void SnakeController::setState(State new_state) { state = new_state; }
bool SnakeController::getInstantMove() { return instantMove; }

void SnakeController::setInstantMove(bool newInstantMove) {
  instantMove = newInstantMove;
}

int SnakeController::getSpeed() { return speed; }

GameInfo_t SnakeController::getGameInfo() { return *model->get_gameInfo(); }

void SnakeController::updateGameState() {
  switch (state) {
    case State::GAME:
      handleGame();
      break;
    case State::EATING:
      handleEating();
      break;
    case State::PAUSE:
      handlePause();
      break;
    case State::GAME_OVER:
      handleGameOver();
      break;
    default:
      break;
  }
}

void SnakeController::handleGame() {
  if (instantMove || timer.tick()) {
    MoveResult result = model->moveSnake();

    if (result.moved) {
      if (result.ateApple) {
        state = State::EATING;
      }
    } else if (!result.moved || model->isWin()) {
      state = State::GAME_OVER;
    }

    instantMove = false;
    timer.reset();
  }
}

void SnakeController::handlePause() { model->setPause(1); }

// 800 - 1 level
// 500 - 10 level
void SnakeController::handleEating() {
  int score = model->get_gameInfo()->score;
  int level = score / 5;

  if (score % 5 == 0 && level <= 10) {
    timer.setInterval(800 - level * 30);
    model->get_gameInfo()->level = level;
    model->get_gameInfo()->speed = level * 10;
  }
  state = State::GAME;
}

void SnakeController::handleGameOver() {
  int current_record = model->get_gameInfo()->score;
  int old_record = model->get_high_score();
  if (current_record > old_record) {
    model->write_high_score();
  }
}

void SnakeController::updateSpeed() {
  int level = model->get_gameInfo()->level;
  int new_interval = 800 - level * 30;
  int new_speed = level * 10;
  if (new_speed != model->get_gameInfo()->speed) {
    timer.setInterval(new_interval);
    model->get_gameInfo()->speed = new_speed;
  }
}

void SnakeController::userInput(UserAction_t user_action, bool hold) {
  (void)hold;
  switch (user_action) {
    case Up:
      turnSnake(user_action);
      break;
    case Down:
      turnSnake(user_action);
      break;
    case Right:
      turnSnake(user_action);
      break;
    case Left:
      turnSnake(user_action);
      break;
    case Pause:
      state = State::PAUSE;
      break;
    case Action:
      instantMove = true;
      break;
    case Start:
      if (state == State::PAUSE) state = State::GAME;
      model->setPause(0);
      break;
    case Terminate:
      state = State::GAME_OVER;
      break;
    default:
      break;
  }
}

Direction SnakeController::toDirection(UserAction_t user_action) {
  switch (user_action) {
    case Up:
      return Direction::UP;
    case Down:
      return Direction::DOWN;
    case Right:
      return Direction::RIGHT;
    case Left:
      return Direction::LEFT;
    default:
      throw std::invalid_argument("Invalid direction");
  }
}

void SnakeController::turnSnake(UserAction_t user_action) {
  Direction dir = toDirection(user_action);
  if (model->changeDirection(dir)) {
    instantMove = true;
  }
}
}  // namespace s21