#ifndef SNAKE_VIEW
#define SNAKE_VIEW

#include <ncurses.h>

#include "../struct.h"
#include "SnakeController.h"

class SnakeView {
 private:
  WINDOW *game_window;
  WINDOW *info_window;
  SnakeController *controller;

 public:
  SnakeView(SnakeController *c) : controller(c) {
    game_window = newwin(HEIGHT + 2, WIDTH * 2 + 2, LINES / 2 - HEIGHT / 2,
                         COLS / 2 - WIDTH - 9);
    box(game_window, 0, 0);

    int x, y;
    getbegyx(game_window, y, x);
    info_window = newwin(HEIGHT + 2, WIDTH + 10, y, x + WIDTH * 2 + 1);
    box(info_window, 0, 0);
    curs_set(0);
  };
  ~SnakeView();

  UserAction_t getUserInput();
  void render(GameInfo_t game_info);
  void update_info_window(GameInfo_t game_info);
  void gameLoop();
};

SnakeView::~SnakeView() {}

void SnakeView::gameLoop() {
  //   controller.state = GAME;
  while (controller->getState() != State::GAME_OVER) {
    UserAction_t user_action = getUserInput();
    controller->userInput(user_action, true);
    controller->updateGameState();
    render(controller->getGameInfo());
  }
  controller->updateGameState();
}

UserAction_t SnakeView::getUserInput() {
  int ch = getch();
  UserAction_t result;

  switch (ch) {
    case '\n':
      result = Start;
      break;
    case 'p':
      result = Pause;
      break;
    case 'q':
      result = Terminate;
      break;
    case KEY_LEFT:
      result = Left;
      break;
    case KEY_RIGHT:
      result = Right;
      break;
    case KEY_UP:
      result = Up;
      break;
    case KEY_DOWN:
      result = Down;
      break;
    case ' ':
      result = Action;
      break;
    default:
      break;
  }
  return result;
}

void SnakeView::render(GameInfo_t game_info) {
  refresh();
  wrefresh(game_window);
  wrefresh(info_window);

  for (int i = 0; i < HEIGHT; i++) {
    for (int k = 0; k < WIDTH; k++) {
      if (game_info.field[i][k] == 1) {
        wattron(game_window, COLOR_PAIR(1));
        mvwprintw(game_window, i + 1, k * 2 + 1, "  ");
        wattroff(game_window, COLOR_PAIR(1));

      } else if (game_info.field[i][k] == 2) {
        wattron(game_window, COLOR_PAIR(5));
        mvwprintw(game_window, i + 1, k * 2 + 1, "  ");
        wattroff(game_window, COLOR_PAIR(5));
      } else {
        wattron(game_window, COLOR_PAIR(2));
        mvwprintw(game_window, i + 1, k * 2 + 1, "  ");
        wattron(game_window, COLOR_PAIR(2));
      }
    }
  }

  update_info_window(game_info);
  wrefresh(game_window);
}

void SnakeView::update_info_window(GameInfo_t game_info) {
  wattron(info_window, COLOR_PAIR(2));
  for (int i = 1; i < HEIGHT + 1; i++) {
    for (int k = 1; k < WIDTH + 9; k++) {
      mvwprintw(info_window, i, k, " ");
    }
  }

  mvwprintw(info_window, 7, 2, "Score: %d", game_info.score);
  mvwprintw(info_window, 9, 2, "Record: %d", game_info.high_score);
  mvwprintw(info_window, 11, 2, "Level: %d", game_info.level);
  mvwprintw(info_window, 13, 2, "Speed: %d", game_info.speed);
  if (game_info.pause == 0) {
    mvwprintw(info_window, 2, WIDTH + 6, "|>");
  } else {
    mvwprintw(info_window, 2, WIDTH + 6, "||");
  }
  wattroff(info_window, COLOR_PAIR(2));
  wrefresh(info_window);
}

#endif