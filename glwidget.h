#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QOpenGLWidget>
#include <QTimer>
#include <QKeyEvent>
#include <QPainter>
#include <QRandomGenerator>
#include <QGuiApplication>
#include <QLabel>
#include <QDateTime> // Include QDateTime for time calculations
#include <QMediaPlayer>
#include <QAudioOutput>
#include <QUrl>
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
    QLabel *scoreCounter;
    QLabel *currentFood;
    QMediaPlayer *player;
    QAudioOutput *audioOutput;
    Direction snakeDirection;
    Food *food;
    int time = 150;
    int cellSize;
    bool snakeMoving;
    bool invulnerable;
    // Add a member variable to store the time of the last movement
    QDateTime lastMoveTime;
    // Add a constant for the cooldown duration (in milliseconds)
    const int movementCooldown = 200; // Adjust this value as needed

    void updateGame();
    void initializeSnake();
    void drawSnake();
    void moveSnake();
    void generateFood();
    void teleportSnake();
    void resetGame();
    void createLabels();
    bool checkCollision();
    QLabel* createLabel(const QString& text, int x, int y);
};

#endif // GLWIDGET_H
