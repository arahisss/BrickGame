#ifndef INFOPANEL_H
#define INFOPANEL_H
#include <QString>
#include <QWidget>

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
  //   void resizeEvent(QResizeEvent* event) override;

 protected:
  void paintEvent(QPaintEvent* e) override;

 private:
  QString scoreText;
  QString recordText;
  QString levelText;
  QString speedText;
  bool isPaused;
};

#endif  // INFOPANEL_H