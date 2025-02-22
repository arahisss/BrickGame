#ifndef TETRISQT_H
#define TETRISQT_H

#include <QKeyEvent>
#include <QPainter>
#include <QTimer>
#include <QWidget>

#include "../../brick_game/struct.h"
#include "../../brick_game/tetris/backend.h"
#include "InfoPanel.h"

namespace s21 {
class TetrisQt : public QWidget {
  Q_OBJECT;

 public:
  TetrisQt();
  InfoPanel* getInfoPanel();
  void setState(GameState new_state);

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
  void nextChanged(int** figure);
  void gameFinished();

 private slots:
  void gameLoop();

 private:
  GameInfo_t gameInfo;
  GameState state = GameState::START;
  UserAction_t lastAction;
  InfoPanel* infoPanel;
  int cellSize;
  QTimer* timer;
  QPixmap bg;
  QFont font;
  QPen pen;
};
}  // namespace s21
#endif