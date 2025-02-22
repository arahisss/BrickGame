#include "mainwindow.h"

#include <QDebug>
#include <QGuiApplication>
#include <QHBoxLayout>
#include <QScreen>
#include <QVBoxLayout>

#include "SnakeQt.h"
namespace s21 {

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent) {
  model = new s21::SnakeModel();
  controller = new s21::SnakeController(model);
  snake = new s21::SnakeQt(controller);
  tetris = new s21::TetrisQt();
  menu = new s21::GameMenu(this);
  stackedWidget = new QStackedWidget(this);
  stackedWidget->addWidget(menu);
  setCentralWidget(stackedWidget);
  connect(menu, &s21::GameMenu::gameSelected, this, &MainWindow::startGame);
  move(QGuiApplication::primaryScreen()->geometry().center() - rect().center());
}

MainWindow::~MainWindow() {
  delete model;
  delete controller;
  delete snake;
  delete tetris;
}

void MainWindow::startGame(const QString& gameName) {
  if (gameName == "Snake") {
    genSnakeWindow();
  } else if (gameName == "Tetris") {
    genTetrisWindow();
  }
}

void MainWindow::resetSnakeGame() {
  if (controller) {
    delete controller;
    controller = nullptr;
  }

  if (model) {
    delete model;
    model = nullptr;
  }
  model = new s21::SnakeModel();
  controller = new s21::SnakeController(model);
  snake = new s21::SnakeQt(controller);
}

void MainWindow::returnToMenu() {
  if (snake) {
    delete snake;
    snake = nullptr;
    resetSnakeGame();
  }
  if (tetris) {
    delete tetris;
    tetris = nullptr;
    tetris = new s21::TetrisQt();
  }
  if (snakeWindow) {
    stackedWidget->removeWidget(snakeWindow);
    snakeWindow->deleteLater();
    snakeWindow = nullptr;
  }

  if (tetrisWindow) {
    stackedWidget->removeWidget(tetrisWindow);
    tetrisWindow->deleteLater();
    tetrisWindow = nullptr;
  }
  stackedWidget->setCurrentIndex(0);
  menu->setFocus();
}

void MainWindow::genSnakeWindow() {
  if (!snakeWindow) {
    snakeWindow = new QWidget(this);
    QVBoxLayout* vLayout = new QVBoxLayout(snakeWindow);
    QHBoxLayout* hLayout = new QHBoxLayout();

    s21::InfoPanel* infoPanel = snake->getInfoPanel();
    infoPanel->setFixedWidth(250);

    hLayout->addStretch();
    hLayout->addWidget(snake);
    hLayout->addSpacing(20);
    hLayout->addWidget(infoPanel);
    hLayout->addStretch();

    vLayout->addStretch();
    vLayout->addLayout(hLayout);
    vLayout->addStretch();
    stackedWidget->addWidget(snakeWindow);

    snake->setFixedSize(WIDTH * 30, HEIGHT * 30);
  }
  stackedWidget->setCurrentIndex(1);
  this->setMinimumSize(WIDTH_WIN, HEIGHT_WIN);
  snake->setState(s21::State::GAME);

  connect(snake, &s21::SnakeQt::gameFinished, this, &MainWindow::returnToMenu);
  snake->setFocus();
}

void MainWindow::genTetrisWindow() {
  if (!tetrisWindow) {
    tetrisWindow = new QWidget(this);
    QVBoxLayout* vLayout = new QVBoxLayout(tetrisWindow);
    QHBoxLayout* hLayout = new QHBoxLayout();

    s21::InfoPanel* infoPanel = tetris->getInfoPanel();
    infoPanel->setFixedWidth(250);

    hLayout->addStretch();
    hLayout->addWidget(tetris);
    hLayout->addSpacing(20);
    hLayout->addWidget(infoPanel);
    hLayout->addStretch();

    vLayout->addStretch();
    vLayout->addLayout(hLayout);
    vLayout->addStretch();
    stackedWidget->addWidget(tetrisWindow);
    tetris->setFixedSize(WIDTH * 30, HEIGHT * 30);
  }

  tetris->setState(GameState::WAITING);
  stackedWidget->setCurrentIndex(1);
  this->setMinimumSize(WIDTH_WIN, HEIGHT_WIN);

  connect(tetris, &s21::TetrisQt::gameFinished, this,
          &MainWindow::returnToMenu);
  tetris->setFocus();
}
}  // namespace s21
