#ifndef SNAKEQT_H
#define SNAKEQT_H

#include <QKeyEvent>
#include <QPainter>
#include <QTimer>
#include <QWidget>

#include "../../../brick_game/snake/SnakeController.h"
#include "../../../brick_game/struct.h"
#include "InfoPanel.h"

#define WIDTH_WIN 700
#define HEIGHT_WIN 600

class SnakeQt : public QWidget {
  Q_OBJECT
 public:
  SnakeQt(SnakeController* c);
  ~SnakeQt();
  InfoPanel* getInfoPanel();

 protected:
  void paintEvent(QPaintEvent* e) override;
  void keyPressEvent(QKeyEvent* event) override;
  void resizeEvent(QResizeEvent* event) override;

 signals:
  void scoreChanged(int score);
  void recordChanged(int record);
  void levelChanged(int level);
  void speedChanged(int speed);
  void pauseChanged(bool isPaused);

 private slots:
  void gameLoop();

 private:
  GameInfo_t gameInfo;
  int cellSize;  // размер ячейки
  QTimer* timer;
  SnakeController* controller;
  UserAction_t lastAction;
  InfoPanel* infoPanel;
  bool isBoosted = false;

  QPixmap bg;
  QFont font;
  QPen pen;
};

#endif