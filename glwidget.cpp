#include "glwidget.h"
#include <QPainter>
#include <QRandomGenerator>

GLWidget::GLWidget(QWidget *parent)
    : QOpenGLWidget(parent),
    snakeDirection(Right),
    timer(new QTimer(this))
{
    connect(timer, &QTimer::timeout, this, &GLWidget::updateGame);
    timer->start(100);
}

GLWidget::~GLWidget()
{
    delete timer;
}

void GLWidget::initializeGL()
{
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glEnable(GL_DEPTH_TEST);

    initializeSnake();
    generateFood();
}

void GLWidget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    drawSnake();

    glFlush();
}

void GLWidget::resizeGL(int width, int height)
{
    glViewport(0, 0, width, height);
}

void GLWidget::keyPressEvent(QKeyEvent *event)
{
    switch (event->key()) {
    case Qt::Key_Up:
        if (snakeDirection != Down)
            snakeDirection = Up;
        break;
    case Qt::Key_Down:
        if (snakeDirection != Up)
            snakeDirection = Down;
        break;
    case Qt::Key_Left:
        if (snakeDirection != Right)
            snakeDirection = Left;
        break;
    case Qt::Key_Right:
        if (snakeDirection != Left)
            snakeDirection = Right;
        break;
    default:
        break;
    }
}

void GLWidget::updateGame()
{
    moveSnake();
    if (checkCollision()) {
        initializeSnake();
        generateFood();
    }
    update();
}

void GLWidget::initializeSnake()
{
    snake.clear();
    snake.append(QPoint(5, 5));
    snake.append(QPoint(4, 5));
    snake.append(QPoint(3, 5));
}

void GLWidget::drawSnake()
{
    QPainter painter(this);
    painter.setPen(Qt::white);
    painter.setBrush(Qt::white);

    for (const auto &segment : snake) {
        painter.drawRect(segment.x() * 10, segment.y() * 10, 10, 10);
    }

    painter.setBrush(Qt::red);
    painter.drawRect(food.x() * 10, food.y() * 10, 10, 10);
}

void GLWidget::moveSnake()
{
    QPoint head = snake.first();
    switch (snakeDirection) {
    case Up:
        head.ry() -= 1;
        break;
    case Down:
        head.ry() += 1;
        break;
    case Left:
        head.rx() -= 1;
        break;
    case Right:
        head.rx() += 1;
        break;
    }
    snake.prepend(head);
    if (head != food)
        snake.removeLast();
    else
        generateFood();
}

void GLWidget::generateFood()
{
    int x = QRandomGenerator::global()->bounded(20);
    int y = QRandomGenerator::global()->bounded(20);
    food = QPoint(x, y);
}

bool GLWidget::checkCollision()
{
    QPoint head = snake.first();
    if (head.x() < 0 || head.x() >= 20 || head.y() < 0 || head.y() >= 20)
        return true;
    for (int i = 1; i < snake.size(); ++i) {
        if (snake[i] == head)
            return true;
    }
    return false;
}
