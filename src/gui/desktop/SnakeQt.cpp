#include "SnakeQt.h"

#include <QDebug>
#include <QPainter>
#include <QPainterPath>
#include <QPen>

SnakeQt::SnakeQt(SnakeController* c) : cellSize(30), controller(c) {
  setFocusPolicy(Qt::StrongFocus);
  setFocus();
  lastAction = UserAction_t::None;
  timer = new QTimer(this);
  infoPanel = new InfoPanel(this);

  connect(timer, &QTimer::timeout, this, &SnakeQt::gameLoop);
  connect(this, &SnakeQt::scoreChanged, infoPanel, &InfoPanel::updateScore);
  connect(this, &SnakeQt::recordChanged, infoPanel, &InfoPanel::updateRecord);
  connect(this, &SnakeQt::levelChanged, infoPanel, &InfoPanel::updateLevel);
  connect(this, &SnakeQt::speedChanged, infoPanel, &InfoPanel::updateSpeed);
  connect(this, &SnakeQt::pauseChanged, infoPanel, &InfoPanel::updatePause);

  bg = QPixmap(width(), height());

  QPainter backgroundPainter(&bg);
  QLinearGradient gradient(0, 0, width(), height());
  gradient.setColorAt(0, QColor(255, 222, 173));
  backgroundPainter.fillRect(rect(), gradient);
  backgroundPainter.end();

  font = QFont("Arial", 16, QFont::Bold);
  pen = QPen(Qt::black);
  pen.setWidth(2);
  timer->start(controller->getSpeed() / 5);
}

SnakeQt::~SnakeQt() { delete timer; }

InfoPanel* SnakeQt::getInfoPanel() { return infoPanel; }

void SnakeQt::gameLoop() {
  int old_speed = controller->getSpeed();
  if (controller->getState() != State::GAME_OVER) {
    controller->updateGameState();
    update();
    if (old_speed != controller->getSpeed()) {
      timer->setInterval(controller->getSpeed());
    }
  } else {
    controller->updateGameState();
    timer->stop();
  }
}

void SnakeQt::keyPressEvent(QKeyEvent* event) {
  isBoosted = false;
  switch (event->key()) {
    case Qt::Key_Left:
      lastAction = UserAction_t::Left;
      break;
    case Qt::Key_Right:
      lastAction = UserAction_t::Right;
      break;
    case Qt::Key_Up:
      lastAction = UserAction_t::Up;
      break;
    case Qt::Key_Down:
      lastAction = UserAction_t::Down;
      break;
    case Qt::Key_Space:
      lastAction = UserAction_t::Action;
      isBoosted = true;
      break;
    case Qt::Key_P:
      lastAction = UserAction_t::Pause;
      break;
    case Qt::Key_Return:
      lastAction = UserAction_t::Start;
      break;
    case Qt::Key_Q:
      lastAction = UserAction_t::Terminate;
      break;
    default:
      lastAction = UserAction_t::None;
      break;
  }
  event->accept();

  if (lastAction != UserAction_t::None) {
    controller->userInput(lastAction, isBoosted);
    update();
  }
}

void SnakeQt::paintEvent(QPaintEvent* e) {
  Q_UNUSED(e);
  QPainter painter(this);
  GameInfo_t gameInfo = controller->getGameInfo();

  painter.drawPixmap(0, 0, bg);
  painter.setFont(font);
  painter.setPen(pen);
  painter.drawRect(QRectF(0, 0, WIDTH * cellSize, HEIGHT * cellSize));

  int padding = 1;
  for (int i = 0; i < HEIGHT; i++) {
    for (int k = 0; k < WIDTH; k++) {
      int size = cellSize - padding * 2;
      int x = k * cellSize + padding;
      int y = i * cellSize + padding;
      if (gameInfo.field[i][k] == 1) {
        painter.fillRect(x, y, size, size, Qt::darkGreen);
      } else if (gameInfo.field[i][k] == 2) {
        painter.fillRect(x, y, size, size, Qt::red);
      }
    }
  }
  emit scoreChanged(gameInfo.score);
  emit recordChanged(gameInfo.high_score);
  emit levelChanged(gameInfo.level);
  emit speedChanged(gameInfo.speed);
  emit pauseChanged(gameInfo.pause);
}

void SnakeQt::resizeEvent(QResizeEvent* event) {
  bg = QPixmap(width(), height());
  QPainter backgroundPainter(&bg);
  QLinearGradient gradient(0, 0, width(), height());
  gradient.setColorAt(0, QColor(255, 222, 173));
  backgroundPainter.fillRect(rect(), gradient);
  backgroundPainter.end();
  QWidget::resizeEvent(event);
}
