#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QOpenGLWidget>
#include <QTimer>
#include <QKeyEvent>
#include <QPainter>
#include <QRandomGenerator>
#include <QGuiApplication>
#include <QLabel>
#include "food.h"

class GLWidget : public QOpenGLWidget
{
    Q_OBJECT

public:
    explicit GLWidget(QWidget *parent = nullptr);
    ~GLWidget() override;

protected:
    void initializeGL() override;
    void paintGL() override;
    void resizeGL(int width, int height) override;
    void keyPressEvent(QKeyEvent *event) override;
    int getTime(){return time;}

private:
    enum Direction { Up, Down, Left, Right };

    QTimer *timer;
    QList<QPoint> snake;
    QLabel *speedLabel; // Declare a pointer to QLabel
    Direction snakeDirection;
    Food *food;
    int time = 150;
    int cellSize;
    bool snakeMoving;
    bool invulnerable;

    void updateGame();
    void initializeSnake();
    void drawSnake();
    void moveSnake();
    void generateFood();
    bool checkCollision();
};

#endif // GLWIDGET_H
