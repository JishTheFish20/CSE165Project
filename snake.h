#ifndef SNAKE_H
#define SNAKE_H

#include <QPoint>

class Snake
{
public:
    Snake();
    ~Snake();

    void setDirection(int direction);
    void move();

    QList<QPoint> getBody();

private:
    QList<QPoint> body;
    int direction;
};

#endif // SNAKE_H
