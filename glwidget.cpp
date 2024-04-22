#include "glwidget.h"
#include <QPainter>
#include <QGuiApplication>


GLWidget::GLWidget(QWidget *parent)
    : QOpenGLWidget(parent),
    snakeDirection(Right),
    timer(new QTimer(this)),
    cellSize(20), // Set a larger size for each cell
    invulnerable(true) // Initialize invulnerability state to true
{
    connect(timer, &QTimer::timeout, this, &GLWidget::updateGame);
    timer->start(150);

    // Get the size of the primary screen
    QRect screenGeometry = QGuiApplication::primaryScreen()->geometry();

    // Set the window size to match the screen size
    setFixedSize(screenGeometry.size());

    // Optionally, you can move the window to the top-left corner of the screen
    move(screenGeometry.topLeft());

    setFocusPolicy(Qt::StrongFocus); // Makes sure that keyboard presses are checked

    food = new Food(this);
}

GLWidget::~GLWidget()
{
    delete timer;
    delete food;
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
    glViewport(0, 0, width/2, height/2);
}

void GLWidget::keyPressEvent(QKeyEvent *event)
{
    switch (event->key()) {
    case Qt::Key_Up:
    case Qt::Key_Down:
    case Qt::Key_Left:
    case Qt::Key_Right:
        snakeMoving = true; // Snake starts moving when a direction key is pressed
        invulnerable = false; // Snake becomes vulnerable when a direction key is pressed
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
        break;
    default:
        break;
    }
}

void GLWidget::updateGame()
{
    moveSnake();
    if (checkCollision() && !invulnerable) { // Check collision only if not invulnerable
        initializeSnake();
        generateFood();
        timer->setInterval(150);
        invulnerable = true; // Snake becomes invulnerable after respawn
    }
    update();
}

void GLWidget::initializeSnake()
{
    // Get the size of the primary screen
    QRect screenGeometry = QGuiApplication::primaryScreen()->geometry();

    // Calculate the number of cells horizontally and vertically based on screen size
    int numCellsX = screenGeometry.width() / cellSize;
    int numCellsY = screenGeometry.height() / cellSize;

    // Calculate the starting position of the snake near the middle of the screen
    int startX = numCellsX / 2;
    int startY = numCellsY / 2;

    // Initialize the snake with a default size of 3 cells
    snake.clear();

    // Spawn the snake head and the rest of the body segments with rightwards momentum
    for (int i = 0; i < 3; ++i) {
        snake.append(QPoint(startX + i, startY)); // Snake body segments with rightwards momentum
    }

    // Set the snake direction to Right
    snakeDirection = Right;
}

void GLWidget::drawSnake()
{
    QPainter painter(this);
    painter.setPen(Qt::white);
    painter.setBrush(Qt::white);

    for (const auto &segment : snake) {
        painter.drawRect(segment.x() * cellSize, segment.y() * cellSize, cellSize, cellSize);
    }

    switch (food->type()) {
    case Food::Normal:
        painter.setBrush(Qt::red);
        break;
    case Food::SpeedBoost:
        painter.setBrush(Qt::yellow);
        break;
    }

    painter.drawRect(food->position().x() * cellSize, food->position().y() * cellSize, cellSize, cellSize);
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
    if (head != food->position())
        snake.removeLast();
    else{
        generateFood();
        switch (food->type()) {
            case Food::Normal:

                break;
            case Food::SpeedBoost:
                if(timer->interval() > 50){
                 timer->setInterval(timer->interval()-50);
                }
                break;
        }
    }
}

void GLWidget::generateFood()
{
    int x = QRandomGenerator::global()->bounded(width() / cellSize);
    int y = QRandomGenerator::global()->bounded(height() / cellSize);
    food->setPosition(QPoint(x, y));

    int randomType = QRandomGenerator::global()->bounded(2); // Assuming you have 3 types of food
    switch (randomType) {
    case 0:
        food->setType(Food::Normal);
        break;
    case 1:
        food->setType(Food::SpeedBoost);
        break;
    }
}

bool GLWidget::checkCollision()
{
    if (invulnerable) // Skip collision detection if invulnerable
        return false;

    QPoint head = snake.first();
    // Check if the head collides with the borders of the playfield
    if (head.x() < 0 || head.x() >= (width() / cellSize) || head.y() < 0 || head.y() >= (height() / cellSize))
        return true;
    // Check if the head collides with the snake's body
    for (int i = 1; i < snake.size(); ++i) {
        if (snake[i] == head)
            return true;
    }
    return false;
}
