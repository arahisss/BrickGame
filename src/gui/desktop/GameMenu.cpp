#include "GameMenu.h"
#define WIDTH_WIN 700
#define HEIGHT_WIN 600
#include <QLabel>
#include <QSpacerItem>
#include <QVBoxLayout>
namespace s21 {
GameMenu::GameMenu(QWidget* parent) : QWidget(parent) {
  QVBoxLayout* vlayout = new QVBoxLayout(this);
  QHBoxLayout* hLayout = new QHBoxLayout();

  QLabel* menuLabel = new QLabel("MENU", this);
  menuLabel->setAlignment(Qt::AlignCenter);
  menuLabel->setStyleSheet("font-size: 24px; font-weight: bold;");

  snakeButton = new QPushButton("Snake", this);
  tetrisButton = new QPushButton("Tetris", this);

  hLayout->addStretch();
  hLayout->addWidget(snakeButton);
  hLayout->addSpacing(20);
  hLayout->addWidget(tetrisButton);
  hLayout->addStretch();

  vlayout->addStretch();
  vlayout->addWidget(menuLabel);
  vlayout->addSpacing(20);
  vlayout->addLayout(hLayout);
  vlayout->addStretch();

  this->setMinimumSize(WIDTH_WIN, HEIGHT_WIN);

  connect(snakeButton, &QPushButton::clicked, this,
          [this]() { emit gameSelected("Snake"); });

  connect(tetrisButton, &QPushButton::clicked, this,
          [this]() { emit gameSelected("Tetris"); });
}
}  // namespace s21