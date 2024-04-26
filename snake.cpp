#include "snake.h"

Snake::Snake(const QSize &boardSize) : dir(Right), boardSize(boardSize) {}

void Snake::draw(QPainter &painter) {
    for (const auto &segment : body) {
        painter.drawRect(segment.x() * 10, segment.y() * 10, 10, 10);
    }
}

void Snake::move() {
    QPoint newHead = body.front();

    switch (dir) {
    case Up:
        newHead.ry() -= 1;
        break;
    case Down:
        newHead.ry() += 1;
        break;
    case Left:
        newHead.rx() -= 1;
        break;
    case Right:
        newHead.rx() += 1;
        break;
    }

    body.prepend(newHead);

    body.removeLast();
}

void Snake::changeDirection(Direction newDirection) {
    dir = newDirection;
}

int Snake::getSnakeSpeed(){
    return snakeSpeed;
}
