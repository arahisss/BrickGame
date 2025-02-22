#include "InfoPanel.h"

#include <QColor>
#include <QFont>
#include <QPainter>

namespace s21 {
InfoPanel::InfoPanel(QWidget* parent) : QWidget(parent) {
  scoreText = "Score: 0";
  recordText = "Record: 0";
  levelText = "Level: 0";
  speedText = "Speed: 0";
}

void InfoPanel::updateScore(int score) {
  scoreText = QString("Score: %1").arg(score);
  update();
}

void InfoPanel::updateRecord(int record) {
  recordText = QString("Record: %1").arg(record);
  update();
}

void InfoPanel::updateLevel(int level) {
  levelText = QString("Level: %1").arg(level);
  update();
}

void InfoPanel::updateSpeed(int speed) {
  speedText = QString("Speed: %1").arg(speed);
  update();
}

void InfoPanel::updatePause(bool isPaused) {
  this->isPaused = isPaused;
  update();
}

void InfoPanel::updateNext(int** figure) {
  if (!figure) {
    hasNextFigure = false;
    return;
  }
  for (int i = 0; i < 5; ++i) {
    for (int j = 0; j < 5; ++j) {
      nextFigure[i][j] = figure[i][j];
    }
  }
  hasNextFigure = true;
  update();
}

void InfoPanel::paintEvent(QPaintEvent* e) {
  Q_UNUSED(e);
  QPainter painter(this);

  QFont font("Arial", 16);
  QPen pen(Qt::black);
  painter.setFont(font);
  painter.setPen(pen);

  int padding = 30;
  painter.drawText(20, padding, scoreText);
  painter.drawText(20, padding + 30, recordText);
  painter.drawText(20, padding + 60, levelText);
  painter.drawText(20, padding + 90, speedText);

  qreal iconSize = 30;
  qreal iconX = width() - iconSize;
  qreal iconY = 10;

  if (isPaused) {
    qreal barWidth = iconSize / 4;
    painter.fillRect(iconX, iconY, barWidth, iconSize, Qt::darkBlue);
    painter.fillRect(iconX + 2 * barWidth, iconY, barWidth, iconSize,
                     Qt::darkBlue);
  } else {
    QPainterPath path;
    path.moveTo(iconX, iconY);
    path.lineTo(iconX, iconY + iconSize);
    path.lineTo(iconX + iconSize, iconY + iconSize / 2);
    path.closeSubpath();
    painter.fillPath(path, Qt::darkBlue);
  }

  if (hasNextFigure) {
    int cellSize = 30;
    QColor figureColor = Qt::darkGreen;

    int xOffset = 20;
    int yOffset = 170;
    int figPadding = 1;
    for (int i = 0; i < 5; i++) {
      for (int j = 0; j < 5; j++) {
        int size = cellSize - figPadding * 2;
        if (nextFigure[i][j] == 1) {
          painter.fillRect((j * cellSize) + xOffset, (i * cellSize) + yOffset,
                           size, size, figureColor);
        }
      }
    }
  }
}
}  // namespace s21