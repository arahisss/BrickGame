#include "SnakeModel.h"
namespace s21 {
SnakeModel::SnakeModel() {
  game_info = new GameInfo_t();
  game_info->field = {new int *[HEIGHT] {}};
  snake = {{7, 5}, {8, 5}, {9, 5}, {10, 5}};  // y, x

  for (int i = 0; i < HEIGHT; i++) {
    game_info->field[i] = new int[WIDTH]{};
  }
  game_info->pause = 0;
  game_info->score = 0;
  game_info->high_score = get_high_score();
  game_info->level = 0;
  game_info->speed = 10;
  updateField();
  generateApple();
};

SnakeModel::~SnakeModel() {
  for (int i = 0; i < HEIGHT; i++) {
    delete[] game_info->field[i];
  }
  delete[] game_info->field;
  delete game_info;
};

GameInfo_t *SnakeModel::get_gameInfo() { return game_info; }
Coords SnakeModel::getSnakeHead() { return snake.front(); }

void SnakeModel::setPause(bool is_set) { game_info->pause = is_set; }
void SnakeModel::setScore(int new_score) { game_info->score = new_score; }

void SnakeModel::updateField() {
  for (auto it = snake.begin(); it != snake.end(); it++) {
    int y = (*it).first;
    int x = (*it).second;
    game_info->field[y][x] = 1;
  }
}

MoveResult SnakeModel::moveSnake() {
  Coords new_front = snake.front();
  switch (direction) {
    case UP:
      new_front.first -= 1;
      break;
    case DOWN:
      new_front.first += 1;
      break;
    case RIGHT:
      new_front.second += 1;
      break;
    case LEFT:
      new_front.second -= 1;
      break;
    default:
      break;
  }
  if (isOutside(new_front) || isCollision(new_front)) {
    return {false, false};
  }

  snake.push_front(new_front);
  bool didEatApple = (apple == new_front);
  if (!didEatApple) {
    game_info->field[snake.back().first][snake.back().second] = 0;
    snake.pop_back();
  } else {
    generateApple();
    game_info->score += 1;
  }
  updateField();

  return {true, didEatApple};
}

void SnakeModel::setApple(Coords new_coords) { apple = new_coords; }

void SnakeModel::generateApple() {
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<> y(0, 19);
  std::uniform_int_distribution<> x(0, 9);

  apple = {y(gen), x(gen)};
  while (!checkApple(apple)) {
    apple = {y(gen), x(gen)};
  }

  game_info->field[apple.first][apple.second] = 2;
}

bool SnakeModel::checkApple(Coords apple) {
  for (auto it = snake.begin(); it != snake.end(); it++) {
    if (*it == apple) {
      return false;
    }
  }
  return true;
}

bool SnakeModel::isOutside(Coords head) {
  if (head.first >= 20 || head.first < 0 || head.second >= 10 ||
      head.second < 0) {
    return true;
  }
  return false;
}

bool SnakeModel::isCollision(Coords head) {
  for (auto it = snake.begin(); it != snake.end(); it++) {
    if (*it == head) {
      return true;
    }
  }
  return false;
}

bool SnakeModel::changeDirection(Direction new_direction) {
  if (checkSameDirection(new_direction) ||
      checkOppositeDirections(new_direction)) {
    return false;
  }

  direction = new_direction;
  return true;
}

bool SnakeModel::checkOppositeDirections(Direction new_direction) {
  return ((direction == UP && new_direction == DOWN) ||
          (direction == DOWN && new_direction == UP) ||
          (direction == RIGHT && new_direction == LEFT) ||
          (direction == LEFT && new_direction == RIGHT));
}

bool SnakeModel::checkSameDirection(Direction new_direction) {
  return ((direction == UP && new_direction == UP) ||
          (direction == DOWN && new_direction == DOWN) ||
          (direction == RIGHT && new_direction == RIGHT) ||
          (direction == LEFT && new_direction == LEFT));
}

int SnakeModel::get_high_score() {
  std::string line;
  std::ifstream in("max_score_snake.txt");
  if (!in.is_open()) {
    return 0;
  }
  std::getline(in, line);
  in.close();
  if (line.length() > 0) {
    return std::stoi(line);
  }
  return 0;
}

bool SnakeModel::isWin() { return game_info->score >= 196; }

void SnakeModel::write_high_score() {
  std::ofstream out;
  out.open("max_score_snake.txt");
  if (out.is_open()) {
    out << std::to_string(game_info->score);
  }
  out.close();
}
}  // namespace s21