#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QOpenGLWidget>
#include <QTimer>
#include <QKeyEvent>
#include <QPainter>
#include <QRandomGenerator>
#include <QGuiApplication>

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

private:
    enum Direction { Up, Down, Left, Right };

    QTimer *timer;
    QList<QPoint> snake;
    QPoint food;
    Direction snakeDirection;
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
