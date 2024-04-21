#include "snake.h"

Snake::Snake(const QSize &boardSize) : dir(Right), boardSize(boardSize) {}

void Snake::draw(QPainter &painter) {
    for (const auto &segment : body) {
        painter.drawRect(segment.x() * 10, segment.y() * 10, 10, 10);
    }
}

void Snake::move() {
    QPoint head = body.front();
    switch (dir) {
    case Up:    head.ry() -= 1; break;
    case Down:  head.ry() += 1; break;
    case Left:  head.rx() -= 1; break;
    case Right: head.rx() += 1; break;
    }
    // Update the rest of the snake's body accordingly
}

void Snake::changeDirection(Direction newDirection) {
    dir = newDirection;
}
