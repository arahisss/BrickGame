#include "mainwindow.h"

#include <QGuiApplication>
#include <QHBoxLayout>
#include <QScreen>
#include <QVBoxLayout>

#include "SnakeQt.h"

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent), controller(&model) {
  snake = new SnakeQt(&controller);
  snake->setFixedSize(WIDTH * 30, HEIGHT * 30);
  InfoPanel* infoPanel = snake->getInfoPanel();
  infoPanel->setFixedWidth(250);

  QWidget* container = new QWidget(this);
  QVBoxLayout* vLayout = new QVBoxLayout(container);
  QHBoxLayout* hLayout = new QHBoxLayout();

  hLayout->addStretch();
  hLayout->addWidget(snake);
  hLayout->addSpacing(20);
  hLayout->addWidget(infoPanel);
  hLayout->addStretch();

  vLayout->addStretch();
  vLayout->addLayout(hLayout);
  vLayout->addStretch();

  setCentralWidget(container);
  this->setMinimumSize(WIDTH_WIN, HEIGHT_WIN);
  move(QGuiApplication::primaryScreen()->geometry().center() - rect().center());
}

MainWindow::~MainWindow() { delete snake; }