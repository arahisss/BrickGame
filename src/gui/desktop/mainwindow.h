#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPointer>
#include <QStackedWidget>

#include "../../brick_game/snake/SnakeController.h"
#include "../../brick_game/snake/SnakeModel.h"
#include "../../brick_game/struct.h"
#include "GameMenu.h"
#include "SnakeQt.h"
#include "TetrisQt.h"

namespace s21 {
class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

 private slots:
  void startGame(const QString &gameName);
  void returnToMenu();
  void resetSnakeGame();
  void genSnakeWindow();
  void genTetrisWindow();

 private:
  s21::SnakeQt *snake;
  s21::TetrisQt *tetris;
  s21::SnakeController *controller;
  s21::SnakeModel *model;
  QPointer<s21::GameMenu> menu;
  QStackedWidget *stackedWidget;
  QPointer<QWidget> snakeWindow;
  QPointer<QWidget> tetrisWindow;
};
}  // namespace s21
#endif
