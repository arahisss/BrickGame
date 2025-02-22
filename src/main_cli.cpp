#include <string>

#include "brick_game/snake/SnakeController.h"
#include "brick_game/snake/SnakeModel.h"
#include "brick_game/snake/SnakeView.h"
#include "brick_game/tetris/backend.h"
#include "gui/cli/frontend.h"

void start_tetris() {
  GameState state = GameState::START;
  init_start(&state);

  GameWindows windows;
  draw_game(&windows);

  while (state != GameState::GAME_OVER) {
    updateGameState(&state);
    UserAction_t user_action = getUserInput();

    game(&state, user_action);
    if (state != GameState::GAME_OVER) {
      render(*getGameInfo(), &windows);
    };
  }
  delwin(windows.game_window);
  delwin(windows.info_window);
}

void start_snake() {
  s21::SnakeModel model;
  s21::SnakeController controller(&model);
  s21::SnakeView view(&controller);

  controller.setState(s21::State::GAME);
  view.gameLoop();
}

void show_menu(int choice) {
  const std::string options[2] = {"Tetris", "Snake"};
  const std::string menu = "MENU";
  int space_between = 5;
  int total_width = options[0].length() + options[1].length() + space_between;

  int x = (COLS - total_width) / 2;
  int y = (LINES - 1) / 2;

  mvprintw(y - 4, COLS / 2 - 2, "%s", menu.c_str());

  for (int i = 0; i < 2; i++) {
    if (i == choice) {
      attron(A_REVERSE);
      mvprintw(y, x + (options[i].length() + space_between) * i, "%s",
               options[i].c_str());
      attroff(A_REVERSE);
    } else {
      mvprintw(y, x + (options[i].length() + space_between) * i, "%s",
               options[i].c_str());
    }
  }
}

int main() {
  init_gui();
  int choice = 0;  // 0 - tetris, 1 - snake
  int new_choice = 0;
  show_menu(choice);
  refresh();

  int key = getch();
  while (key != 27) {
    switch (key) {
      case KEY_RIGHT:
        new_choice = (choice - 1 + 2) % 2;
        break;
      case KEY_LEFT:
        new_choice = (choice + 1) % 2;
        break;
      case 10:
        clear();
        if (choice == 0) {
          start_tetris();
          touchwin(stdscr);
          refresh();
        } else {
          start_snake();
        }
        clear();
        show_menu(choice);
        break;
      default:
        break;
    }
    if (choice != new_choice) {
      choice = new_choice;
      clear();
      show_menu(choice);
      refresh();
    }
    key = getch();
  }
  endwin();
  clean_gameInfo();
  clean_gameData();

  return 0;
}