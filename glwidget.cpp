#include "glwidget.h"
#include "food.h"
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

    QRect screenGeometry = QGuiApplication::primaryScreen()->geometry();

    setFixedSize(screenGeometry.size().width()/1.5, screenGeometry.size().height()/1.5);



    // Optionally, you can move the window to the top-left corner of the screen
    //move(screenGeometry.topLeft());

    createLabels();

    setFocusPolicy(Qt::StrongFocus); // Makes sure that keyboard presses are checked

    food = new Food(this);
    teleportFood = new TeleportFood(this);

    exit = createLabel("Exit", newHeadPosition.x() * cellSize, newHeadPosition.y() * cellSize);
    exit->hide();
    Score = 0;

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
    // Generate initial food
    food = Food::generateRandomFood(width(), height(), cellSize);
    teleportFood->setTeleportPosition(width(), height(), cellSize);
    updateLabels();
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
    //qDebug() << "Generated food name:" << food->getName(); // Debug output to check the name of the new food
    moveSnake();
    if (checkCollision() && !invulnerable) { // Check collision only if not invulnerable
        resetGame();
    }
    update();
}

void GLWidget::initializeSnake()
{
    QRect screenGeometry = QGuiApplication::primaryScreen()->geometry();

    int numCellsX = screenGeometry.width() / 2 / cellSize;
    int numCellsY = screenGeometry.height() / 2 / cellSize;

    int startX = numCellsX / 2;
    int startY = numCellsY / 2;

    snake.clear();

    for (int i = 0; i < 3; ++i) {
        snake.append(QPoint(startX + i, startY));
    }

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
        //exit->show(); // Show the label
        painter.setBrush(QColorConstants::Svg::orange);
        newHeadPosition = teleportFood->getTeleportPosition();
        painter.drawRect(newHeadPosition.x() * cellSize, newHeadPosition.y() * cellSize, cellSize, cellSize);
        painter.setBrush(Qt::green);
        break;
    }


    painter.drawRect(food->position().x() * cellSize, food->position().y() * cellSize, cellSize, cellSize);
    updateLabels();
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
            if(timer->interval() > 20){
                timer->setInterval(timer->interval()-20);
            }
            break;
        case Food::SnailEffect:
            if((150 - timer->interval()) > 0){
                timer->setInterval(timer->interval()+20);
            }
            break;
        case Food::TeleportFruit:
            teleportSnake();
            break;
        }
        food = Food::generateRandomFood(width(), height(), cellSize);
        teleportFood->setTeleportPosition(width(), height(), cellSize);
        updateLabels();
    }
}


void GLWidget::teleportSnake()
{
    snake[0] = newHeadPosition;

}

bool GLWidget::checkCollision()
{
    if (invulnerable)
        return false;

    QPoint head = snake.first();
    if (head.x() < 0 || head.x() >= (width() / cellSize) || head.y() < 0 || head.y() >= (height() / cellSize))
        return true;
    for (int i = 0; i < snake.size(); ++i) {
        if (i != 0 && snake[i] == head) // Skip the comparison with the head itself
            return true;
    }
    return false;
}

void GLWidget::createLabels() {
    // Create labels with adjusted positions
    speedLabel = createLabel("Speed: 0           ", 0, 0);
    scoreCounter = createLabel("Score: 0          ", 200, 0);
    currentFood = createLabel("Fruit: N/A                              ", 400, 0);
    bestScore = createLabel("Best Score:          ", 800,0);
}

QLabel* GLWidget::createLabel(const QString& text, int x, int y) {
    QLabel* label = new QLabel(text, this);
    label->setStyleSheet("color: white; font-size: 15pt;");
    label->move(x, y);
    label->raise();
    label->show();
    return label;
}

void GLWidget::resetGame()
{
    if(Score < (snake.size() - 3) * 10){
        Score = (snake.size() - 3) * 10;
    }
    bestScore->setText(QString("Best Score: %1").arg(Score));
    initializeSnake();
    timer->setInterval(getTime());

    food = Food::generateRandomFood(width(), height(), cellSize);
    teleportFood->setTeleportPosition(width(), height(), cellSize);

    updateLabels();

    invulnerable = true;
}

void GLWidget::updateLabels(){
    currentFood->setText(QString("Current: %1").arg(food->getName()));
    speedLabel->setText(QString("Speed: %1").arg(150 - timer->interval()));
    scoreCounter->setText(QString("Score: %1").arg((snake.size() - 3) * 10));
    exit->move(newHeadPosition.x() * cellSize, newHeadPosition.y() * cellSize);

    if (food->getName() == "TeleportFood") {
        exit->show();
    }else{
        exit->hide();
    }
}
