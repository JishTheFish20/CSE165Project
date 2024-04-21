#include "glwidget.h"
#include <QPainter>
#include <QRandomGenerator>
#include <QGuiApplication>

GLWidget::GLWidget(QWidget *parent)
    : QOpenGLWidget(parent),
    snakeDirection(Right),
    timer(new QTimer(this))
{
    connect(timer, &QTimer::timeout, this, &GLWidget::updateGame);
    timer->start(100);

    QRect screenGeometry = QGuiApplication::primaryScreen()->geometry();
    setFixedSize(screenGeometry.size());
    move(screenGeometry.topLeft());

    setFocusPolicy(Qt::StrongFocus); // Makes sure that keyboard presses are checked
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
    QRect screenGeometry = QGuiApplication::primaryScreen()->geometry();
    int numCellsX = screenGeometry.width() / 15;
    int numCellsY = screenGeometry.height() / 15;

    snake.clear();

    // Randomly spawn the snake within the bounds
    int headX = QRandomGenerator::global()->bounded(numCellsX - 2) + 1; // Exclude edges
    int headY = QRandomGenerator::global()->bounded(numCellsY - 2) + 1; // Exclude edges
    snake.append(QPoint(headX, headY)); // Snake head

    for (int i = 1; i < 3; ++i) {
        snake.append(QPoint(headX - i, headY)); // Adjacent cells to the left
    }
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
    QRect screenGeometry = QGuiApplication::primaryScreen()->geometry();
    int numCellsX = screenGeometry.width() / 15;
    int numCellsY = screenGeometry.height() / 15;

    int x = QRandomGenerator::global()->bounded(numCellsX);
    int y = QRandomGenerator::global()->bounded(numCellsY);
    food = QPoint(x, y);
}

bool GLWidget::checkCollision()
{
    QPoint head = snake.first();
    QRect screenGeometry = QGuiApplication::primaryScreen()->geometry();
    int numCellsX = screenGeometry.width() / 15;
    int numCellsY = screenGeometry.height() / 15;

    if (head.x() <= 0 || head.x() >= numCellsX - 1 || head.y() <= 0 || head.y() >= numCellsY - 1)
        return true;
    for (int i = 1; i < snake.size(); ++i) {
        if (snake[i] == head)
            return true;
    }
    return false;
}
