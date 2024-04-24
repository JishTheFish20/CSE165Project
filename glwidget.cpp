#include "glwidget.h"
#include <QPainter>
#include <QGuiApplication>


GLWidget::GLWidget(QWidget *parent)
    : QOpenGLWidget(parent),
    timer(new QTimer(this)),
    snakeDirection(Right),
    cellSize(20), // Set a larger size for each cell
    invulnerable(true) // Initialize invulnerability state to true
{

    connect(timer, &QTimer::timeout, this, &GLWidget::updateGame);
    timer->start(getTime());

    // Get the size of the primary screen
    QRect screenGeometry = QGuiApplication::primaryScreen()->geometry();

    // Set the window size to match the screen size
    setFixedSize(screenGeometry.size().width()/1.5, screenGeometry.size().height()/1.5);



    // Optionally, you can move the window to the top-left corner of the screen
    //move(screenGeometry.topLeft());

    speedLabel = new QLabel("Speed: N/A", this);
    speedLabel->setStyleSheet("color: white; font-size: 15pt;"); // Set text color to white and font size to 20 points
    speedLabel->move(200, 0); // Adjust the position of the label as needed
    speedLabel->raise();
    speedLabel->show(); // Ensure the label is visible

    scoreCounter = new QLabel("Score: N/A", this);
    scoreCounter->setStyleSheet("color: white; font-size: 15pt;"); // Set text color to white and font size to 20 points
    scoreCounter->move(50, 0); // Adjust the position of the label as needed
    scoreCounter->raise();
    scoreCounter->show(); // Ensure the label is visible

    currentFood = new QLabel("Fruit: N/A", this);
    currentFood->setStyleSheet("color: white; font-size: 15pt;"); // Set text color to white and font size to 20 points
    currentFood->move(300, 0); // Adjust the position of the label as needed
    currentFood->raise();
    currentFood->show(); // Ensure the label is visible

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
    glViewport(0, 0, width/1.5, height/1.5);
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
    speedLabel->setText(QString("Speed: %1").arg(150 - timer->interval()));
    scoreCounter->setText(QString("Score: %1").arg((snake.size() - 3) * 10));
    moveSnake();
    if (checkCollision() && !invulnerable) { // Check collision only if not invulnerable
        initializeSnake();
        generateFood();
        timer->setInterval(getTime());
        invulnerable = true; // Snake becomes invulnerable after respawn
    }
    update();
}

void GLWidget::initializeSnake()
{
    // Get the size of the primary screen
    QRect screenGeometry = QGuiApplication::primaryScreen()->geometry();

    // Calculate the number of cells horizontally and vertically based on screen size
    int numCellsX = screenGeometry.width() / 2 / cellSize;
    int numCellsY = screenGeometry.height() / 2 / cellSize;

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
    case Food::SnailEffect:
        painter.setBrush(Qt::blue);
        break;
    case Food::TeleportFruit:
        painter.setBrush(Qt::green);
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
        switch (food->type()) {
        case Food::Normal:

            break;
        case Food::SpeedBoost:
            if(timer->interval() > 50){
                timer->setInterval(timer->interval()-20);
            }
            break;
        case Food::SnailEffect:
            timer->setInterval(timer->interval()+20);
            break;
        case Food::TeleportFruit:
            teleportSnake();
            break;
        }
        generateFood();
    }
}

void GLWidget::generateFood()
{
    int x = QRandomGenerator::global()->bounded(width() / cellSize);
    int y = QRandomGenerator::global()->bounded(height() / cellSize);
    food->setPosition(QPoint(x, y));

    int randomType = QRandomGenerator::global()->bounded(4); // Assuming you have 3 types of food
    switch (randomType) {
    case 0:
        food->setType(Food::Normal);
        currentFood->setText(QString("Food: Normal"));
        break;
    case 1:
        food->setType(Food::SpeedBoost);
        currentFood->setText(QString("Food: Speed"));
        break;
    case 2:
        food->setType(Food::SnailEffect);
        currentFood->setText(QString("Food: Slow"));
        break;
    case 3:
        food->setType(Food::TeleportFruit);
        currentFood->setText(QString("Food: Portal"));
        break;
    }
}

void GLWidget::teleportSnake()
{
    int x = QRandomGenerator::global()->bounded(width() / cellSize);
    int y = QRandomGenerator::global()->bounded(height() / cellSize);
    QPoint newHeadPosition(x, y);

    // Clear the old snake head and update it with the new position
    snake[0] = newHeadPosition;
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
    for (int i = 0; i < snake.size(); ++i) {
        if (i != 0 && snake[i] == head) // Skip the comparison with the head itself
            return true;
    }
    return false;
}
