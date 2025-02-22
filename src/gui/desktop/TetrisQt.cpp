#include "TetrisQt.h"

#include <QElapsedTimer>
#include <QPainter>
#include <QPainterPath>
#include <QPen>

namespace s21 {
TetrisQt::TetrisQt() : cellSize(30) {
  setFocusPolicy(Qt::StrongFocus);
  setFocus();
  timer = new QTimer(this);
  lastAction = UserAction_t::None;
  infoPanel = new InfoPanel(this);
  state = GameState::START;

  connect(timer, &QTimer::timeout, this, &TetrisQt::gameLoop);
  connect(this, &TetrisQt::scoreChanged, infoPanel, &InfoPanel::updateScore);
  connect(this, &TetrisQt::recordChanged, infoPanel, &InfoPanel::updateRecord);
  connect(this, &TetrisQt::levelChanged, infoPanel, &InfoPanel::updateLevel);
  connect(this, &TetrisQt::speedChanged, infoPanel, &InfoPanel::updateSpeed);
  connect(this, &TetrisQt::pauseChanged, infoPanel, &InfoPanel::updatePause);
  connect(this, &TetrisQt::nextChanged, infoPanel, &InfoPanel::updateNext);

  bg = QPixmap(width(), height());

  QPainter backgroundPainter(&bg);
  QLinearGradient gradient(0, 0, width(), height());
  gradient.setColorAt(0, QColor(255, 222, 173));
  backgroundPainter.fillRect(rect(), gradient);
  backgroundPainter.end();

  font = QFont("Arial", 16, QFont::Bold);
  pen = QPen(Qt::black);
  pen.setWidth(2);

  timer->start(1000 / 60);
}

InfoPanel* TetrisQt::getInfoPanel() { return infoPanel; }
void TetrisQt::setState(GameState new_state) { state = new_state; }

void TetrisQt::gameLoop() {
  struct timespec current_time;
  clock_gettime(CLOCK_MONOTONIC, &current_time);
  if (state != GameState::GAME_OVER) {
    updateGameState(&state);
    gameQt(&state, lastAction, current_time);
    lastAction = UserAction_t::None;
    if (state != GameState::GAME_OVER) {
      update();
    }
  } else {
    updateGameState(&state);
    timer->stop();
    emit gameFinished();
  }
}

void TetrisQt::keyPressEvent(QKeyEvent* event) {
  switch (event->key()) {
    case Qt::Key_Left:
      lastAction = UserAction_t::Left;
      break;
    case Qt::Key_Right:
      lastAction = UserAction_t::Right;
      break;
    case Qt::Key_Down:
      lastAction = UserAction_t::Down;
      break;
    case Qt::Key_Space:
      lastAction = UserAction_t::Action;
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
}

void TetrisQt::paintEvent(QPaintEvent* e) {
  Q_UNUSED(e);
  QPainter painter(this);
  GameInfo_t* gameInfo = getGameInfo();

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
      if (gameInfo->field[i][k] == 1) {
        painter.fillRect(x, y, size, size, Qt::darkBlue);
      }
    }
  }

  emit scoreChanged(gameInfo->score);
  emit recordChanged(gameInfo->high_score);
  emit levelChanged(gameInfo->level);
  emit speedChanged(gameInfo->speed);
  emit pauseChanged(gameInfo->pause);
  emit nextChanged(gameInfo->next);
}

void TetrisQt::resizeEvent(QResizeEvent* event) {
  bg = QPixmap(width(), height());
  QPainter backgroundPainter(&bg);
  QLinearGradient gradient(0, 0, width(), height());
  gradient.setColorAt(0, QColor(255, 222, 173));
  backgroundPainter.fillRect(rect(), gradient);
  backgroundPainter.end();
  QWidget::resizeEvent(event);
}
}  // namespace s21