#include "snake.h"

Snake::Snake(const QSize &boardSize) : dir(Right), boardSize(boardSize) {
    int initX = boardSize.width() / 2;
    int initY = boardSize.height() / 2;
    segments.emplace_back(initX, initY);
}

void Snake::draw(QPainter &painter) {
    painter.setBrush(Qt::green);
    for (const QPoint &segment : segments) {
        painter.drawRect(segment.x() * 10, segment.y() * 10, 10, 10);
    }
}

void Snake::move() {
    QPoint head = segments.front();
    switch (dir) {
        case Up:    head.ry() -= 1; break;
        case Down:  head.ry() += 1;        case Left:  head.rx() -= 1; break;
        case Right: head.rx() += 1; break;
    }
    segments.insert(segments.begin(), head); // Move head to the new position
    segments.pop_back(); // Remove the last segment to simulate movement
}

void Snake::changeDirection(Direction newDirection) {
    // Prevent reversing direction directly
    if ((dir == Up && newDirection != Down) ||
        (dir == Down && newDirection != Up) ||
        (dir == Left && newDirection != Right) ||
        (dir == Right && newDirection != Left)) {
        dir = newDirection;
    }
}
