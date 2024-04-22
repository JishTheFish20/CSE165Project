#include "snake.h"

Snake::Snake(const QSize &boardSize) : dir(Right), boardSize(boardSize) {}

void Snake::draw(QPainter &painter) {
    for (const auto &segment : body) {
        painter.drawRect(segment.x() * 10, segment.y() * 10, 10, 10);
    }
}

void Snake::move() {
    // Get the current position of the head
    QPoint newHead = body.front();

    // Calculate the new position of the head based on the current direction
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

    // Add the new head to the front of the body
    body.prepend(newHead);

    // Remove the last segment of the body to maintain the snake's length
    body.removeLast();
}

void Snake::changeDirection(Direction newDirection) {
    dir = newDirection;
}

int Snake::getSnakeSpeed(){
    return snakeSpeed;
}
