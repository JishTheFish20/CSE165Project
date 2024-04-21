#ifndef SNAKE_H
#define SNAKE_H

#include <QList>
#include <QPoint>
#include <QPainter>

class Snake
{
public:
    enum Direction { Up, Down, Left, Right };
    Snake(const QSize &boardSize);
    void draw(QPainter &painter);
    void move();
    void changeDirection(Direction newDirection);

private:
    QList<QPoint> body;
    Direction dir;
    QSize boardSize;
};

#endif // SNAKE_H
