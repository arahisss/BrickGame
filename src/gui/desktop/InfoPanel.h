#ifndef INFOPANEL_H
#define INFOPANEL_H
#include <QString>
#include <QWidget>
#include <array>
#include <memory>

namespace s21 {
class InfoPanel : public QWidget {
  Q_OBJECT
 public:
  explicit InfoPanel(QWidget* parent = nullptr);

 public slots:
  void updateScore(int score);
  void updateRecord(int record);
  void updateLevel(int level);
  void updateSpeed(int speed);
  void updatePause(bool isPaused);
  void updateNext(int** figure);

 protected:
  void paintEvent(QPaintEvent* e) override;

 private:
  QString scoreText;
  QString recordText;
  QString levelText;
  QString speedText;
  bool isPaused = false;
  std::array<std::array<int, 5>, 5> nextFigure;
  bool hasNextFigure = false;
};
}  // namespace s21
#endif