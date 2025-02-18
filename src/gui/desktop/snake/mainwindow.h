#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "../../../brick_game/snake/SnakeController.h"
#include "../../../brick_game/snake/SnakeModel.h"
#include "../../../brick_game/struct.h"
#include "SnakeQt.h"

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

 private:
  SnakeQt *snake;
  SnakeController controller;
  SnakeModel model;
};
#endif  // MAINWINDOW_H
