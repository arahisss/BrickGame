#ifndef STRUCT_H
#define STRUCT_H

#define WIDTH 10
#define HEIGHT 20

typedef struct {
  int **field;
  int **next;
  int score;
  int high_score;
  int level;
  int speed;
  int pause;
} GameInfo_t;

typedef enum {
  Start,
  Pause,
  Terminate,
  Action,
  Left,
  Right,
  Up,
  Down,
  None,
} UserAction_t;

struct MoveResult {
  bool moved;
  bool ateApple;
};

#endif