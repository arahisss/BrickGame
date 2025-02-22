
// #include <gtest/gtest.h>

#include <iostream>
#include <stdexcept>

// #include "SnakeController.h"
#include "tests.h"

namespace s21 {
class SnakeControllerTest : public ::testing::Test {
 protected:
  void SetUp() override {
    model = new SnakeModel();
    controller = new SnakeController(model);
  }

  void TearDown() override {
    delete controller;
    delete model;
  }

  SnakeModel* model;
  SnakeController* controller;
};

// TEST_F(SnakeModelTest, ConstructorDestructor) { ASSERT_NE(model, nullptr); }

// Тест для getSpeed (нуждается в настройке getGameInfo в Mock)
TEST_F(SnakeControllerTest, GetSpeed) {
  ASSERT_EQ(controller->getSpeed(), 800);
}

TEST_F(SnakeControllerTest, GetGameInfo) {
  ASSERT_EQ(controller->getGameInfo().score, model->get_gameInfo()->score);
}

// Тесты для геттеров и сеттеров
TEST_F(SnakeControllerTest, GetAndSetState) {
  controller->setState(State::PAUSE);
  ASSERT_EQ(controller->getState(), State::PAUSE);
  controller->setState(State::GAME);
  ASSERT_EQ(controller->getState(), State::GAME);
}

TEST_F(SnakeControllerTest, HandleGameSuccess) {
  controller->setState(State::PAUSE);
  controller->userInput(UserAction_t::Start, false);

  ASSERT_EQ(controller->getState(), State::GAME);
  controller->updateGameState();
}

// Тест handleGame() - съедание яблока
TEST_F(SnakeControllerTest, HandleGameEatApple) {
  controller->setState(State::GAME);
  Coords head = model->getSnakeHead();
  model->setApple({head.first - 1, head.second});  // Яблоко перед головой
  model->setScore(4);
  controller->setInstantMove(true);
  controller->updateGameState();
  ASSERT_EQ(controller->getState(), State::EATING);

  controller->updateGameState();
  ASSERT_EQ(controller->getGameInfo().score, 5);
  ASSERT_EQ(controller->getState(), State::GAME);
  ASSERT_EQ(controller->getGameInfo().level, 1);
}

TEST_F(SnakeControllerTest, updateSpeed) {
  controller->updateSpeed();
  ASSERT_EQ(controller->getSpeed(), 800);
}

TEST_F(SnakeControllerTest, handlePause) {
  controller->userInput(UserAction_t::Pause, false);
  controller->updateGameState();

  ASSERT_EQ(controller->getGameInfo().pause, 1);
}

TEST_F(SnakeControllerTest, HandleGameOver) {
  controller->userInput(UserAction_t::Terminate, false);
  controller->setInstantMove(true);

  for (int i = 0; i < 20; ++i) {
    model->moveSnake();
  }

  controller->updateGameState();
  ASSERT_EQ(controller->getState(), State::GAME_OVER);
  controller->updateGameState();
}

TEST_F(SnakeControllerTest, UserInput) {
  controller->userInput(UserAction_t::Right, false);
  ASSERT_EQ(controller->getInstantMove(), true);

  controller->userInput(UserAction_t::Down, false);
  ASSERT_EQ(controller->getInstantMove(), true);

  controller->userInput(UserAction_t::Action, false);
  ASSERT_EQ(controller->getInstantMove(), true);

  controller->userInput(UserAction_t::Left, false);
  ASSERT_EQ(controller->getInstantMove(), true);

  controller->userInput(UserAction_t::Up, false);
  ASSERT_EQ(controller->getInstantMove(), true);
}

TEST(TimerTest, TimerTests) {
  Timer timer(550);
  timer.setInterval(0.1);

  ASSERT_EQ(timer.tick(), true);
}
}  // namespace s21