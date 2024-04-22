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
    int getSnakeSpeed();
    void setSnakeSpeed(int &speed){snakeSpeed = speed;}

private:
    QList<QPoint> body;
    Direction dir;
    QSize boardSize;
    int snakeSpeed = 150;
};

#endif // SNAKE_H
