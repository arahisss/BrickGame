#include "../brick_game/snake/SnakeModel.h"
#include "tests.h"

namespace s21 {
TEST(SnakeModelTest, Initialization) {
  SnakeModel model;

  EXPECT_EQ(model.get_gameInfo()->score, 0);
  EXPECT_EQ(model.get_gameInfo()->level, 0);
  EXPECT_EQ(model.get_gameInfo()->speed, 10);
  EXPECT_FALSE(model.get_gameInfo()->pause);

  auto field = model.get_gameInfo()->field;
  EXPECT_EQ(field[7][5], 1);
  EXPECT_EQ(field[8][5], 1);
  EXPECT_EQ(field[9][5], 1);
  EXPECT_EQ(field[10][5], 1);
}

TEST(SnakeModelTest, MoveSnake) {
  SnakeModel model;
  model.changeDirection(RIGHT);
  auto result = model.moveSnake();
  EXPECT_TRUE(result.moved);

  auto field = model.get_gameInfo()->field;

  EXPECT_EQ(field[7][6], 1);
  EXPECT_EQ(field[10][5], 0);

  model.changeDirection(UP);
  model.moveSnake();

  EXPECT_EQ(field[6][6], 1);
  EXPECT_EQ(field[9][5], 0);

  model.changeDirection(RIGHT);
  model.moveSnake();
  model.changeDirection(DOWN);
  model.moveSnake();

  EXPECT_EQ(field[7][7], 1);
  //   EXPECT_EQ(field[7][5], 0);
}

TEST(SnakeModelTest, CollisionWithWall) {
  SnakeModel model;

  model.changeDirection(LEFT);
  for (int i = 0; i < 5; ++i) {
    model.moveSnake();
  }

  auto result = model.moveSnake();
  EXPECT_FALSE(result.moved);
}

TEST(SnakeModelTest, GenerateApple) {
  SnakeModel model;

  auto field = model.get_gameInfo()->field;
  bool appleFound = false;
  for (int i = 0; i < HEIGHT; ++i) {
    for (int j = 0; j < WIDTH; ++j) {
      if (field[i][j] == 2) {
        appleFound = true;
        break;
      }
    }
  }
  EXPECT_TRUE(appleFound);
}

TEST(SnakeModelTest, EatApple) {
  SnakeModel model;

  model.changeDirection(RIGHT);
  model.moveSnake();
  model.moveSnake();

  model.setApple({7, 8});

  auto result = model.moveSnake();

  EXPECT_TRUE(result.moved);
  EXPECT_TRUE(result.ateApple);
  EXPECT_EQ(model.get_gameInfo()->score, 1);
}

TEST(SnakeModelTest, ChangeDirection) {
  SnakeModel model;

  EXPECT_TRUE(model.changeDirection(RIGHT));
  EXPECT_FALSE(model.changeDirection(LEFT));
  EXPECT_FALSE(model.changeDirection(RIGHT));
}

TEST(SnakeModelTest, WriteHighScore) {
  SnakeModel model;

  model.get_gameInfo()->score = 100;
  model.write_high_score();

  EXPECT_EQ(model.get_high_score(), 100);
}

TEST(SnakeModelTest, SetPause) {
  SnakeModel model;
  model.setPause(true);
  auto result = model.get_gameInfo();

  EXPECT_TRUE(result->pause);
}

TEST(SnakeModelTest, Collistion) {
  SnakeModel model;
  model.changeDirection(RIGHT);
  model.moveSnake();
  model.changeDirection(DOWN);
  model.moveSnake();
  model.changeDirection(LEFT);
  model.moveSnake();
  EXPECT_TRUE(model.isCollision(model.getSnakeHead()));
}
}  // namespace s21