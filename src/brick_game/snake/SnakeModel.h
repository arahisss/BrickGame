#ifndef SNAKE_MODEL
#define SNAKE_MODEL

#include <deque>
#include <fstream>
#include <iostream>
#include <random>

#include "../struct.h"
namespace s21 {
typedef enum { LEFT, RIGHT, UP, DOWN } Direction;

/**
 * @class SnakeModel
 * @brief Модель для игры "Змейка".
 *
 * Класс SnakeController отвечает за управление логикой игры "Змейка".
 * Он содержит информацию о состоянии игрового поля, положении змейки, яблока
 и текущем направлении движения
 * @param game_info структура для хранения всей информации об игре
 * @param snake очередь для хранения координат змейки
 * @param apple координаты яблока
 * @param direction направление передвижения змейки
 *
 */
using Coords = std::pair<int, int>;
class SnakeModel {
 private:
  GameInfo_t *game_info;
  std::deque<Coords> snake;
  Coords apple;
  Direction direction = UP;

 public:
  SnakeModel();
  virtual ~SnakeModel();
  virtual GameInfo_t *get_gameInfo();
  Coords getSnakeHead();
  virtual MoveResult moveSnake();
  void setApple(Coords new_coords);
  void updateField();
  void setScore(int new_score);
  virtual bool changeDirection(Direction new_direction);
  bool checkSameDirection(Direction new_direction);
  bool checkOppositeDirections(Direction new_direction);
  void generateApple();
  bool checkApple(Coords apple);
  bool isOutside(Coords head);
  bool isCollision(Coords head);
  bool isWin();
  virtual void setPause(bool is_set);
  virtual int get_high_score();
  virtual void write_high_score();
};
}  // namespace s21
#endif