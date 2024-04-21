#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QtOpenGLWidgets/QOpenGLWidget>
#include <QTimer>
#include <QKeyEvent>
#include <QRandomGenerator>
#include <QScreen>

class GLWidget : public QOpenGLWidget
{
    Q_OBJECT

public:
    GLWidget(QWidget *parent = nullptr);
    ~GLWidget();

protected:
    void initializeGL() override;
    void paintGL() override;
    void resizeGL(int width, int height) override;
    void keyPressEvent(QKeyEvent *event) override;

private slots:
    void updateGame();

private:
    void initializeSnake();
    void drawSnake();
    void moveSnake();
    void generateFood();
    bool checkCollision();

    enum Direction { Up, Down, Left, Right };
    Direction snakeDirection;
    QPoint food;
    QList<QPoint> snake;
    QTimer *timer;

    int numCellsX; // Number of cells in the X direction
    int numCellsY; // Number of cells in the Y direction
    int cellSize = 10; // Size of each cell in pixels
};

#endif // GLWIDGET_H
