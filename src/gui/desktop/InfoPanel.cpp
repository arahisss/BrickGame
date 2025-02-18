#include "InfoPanel.h"

#include <QFont>
#include <QPainter>

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
}

// void drawPlayIcon(QPainter& painter, qreal x, qreal y, qreal size) {
//   QPainterPath path;
//   path.moveTo(x, y);                    // Начальная точка
//   path.lineTo(x, y + size);             // Вниз
//   path.lineTo(x + size, y + size / 2);  // Вправо и вверх
//   path.closeSubpath();                  // Замыкаем треугольник
//   painter.fillPath(path, Qt::green);    // Заливаем зеленым
// }

// void drawPauseIcon(QPainter& painter, qreal x, qreal y, qreal size) {
//   qreal barWidth = size / 4;  // Ширина одного прямоугольника
//   painter.fillRect(x, y, barWidth, size, Qt::yellow);  // Левый прямоугольник
//   painter.fillRect(x + 2 * barWidth, y, barWidth, size,
//                    Qt::yellow);  // Правый прямоугольник
// }