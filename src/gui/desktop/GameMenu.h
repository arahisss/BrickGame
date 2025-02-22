#ifndef GAME_MENU
#define GAME_MENU

#include <QPushButton>
#include <QWidget>
namespace s21 {
class GameMenu : public QWidget {
  Q_OBJECT
 public:
  explicit GameMenu(QWidget *parent = nullptr);

 signals:
  void gameSelected(const QString &gameName);

 private:
  QPushButton *snakeButton;
  QPushButton *tetrisButton;
};
}  // namespace s21
#endif