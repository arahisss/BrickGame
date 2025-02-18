#ifndef SNAKE_MODEL
#define SNAKE_MODEL

#include <deque>
#include <fstream>
#include <iostream>
#include <random>

#include "../struct.h"

typedef enum { LEFT, RIGHT, UP, DOWN } Direction;

using Coords = std::pair<int, int>;
class SnakeModel {
 private:
  GameInfo_t *game_info;
  std::deque<Coords> snake;
  Coords apple;
  Direction direction = UP;

 public:
  SnakeModel();
  ~SnakeModel();

  GameInfo_t *get_gameInfo();
  MoveResult moveSnake();
  void updateField();
  bool changeDirection(Direction new_direction);
  bool checkSameDirection(Direction new_direction);
  bool checkOppositeDirections(Direction new_direction);
  void generateApple();
  bool checkApple(Coords apple);
  bool isOutside(Coords head);
  bool isCollision(Coords head);
  void setPause(bool is_set);
  int get_high_score();
  void write_high_score();
};

#endif