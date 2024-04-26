// Food.cpp
#include "Food.h"
#include "SlowFood.h"
#include "SpeedFood.h"
#include "TeleportFood.h"

Food::Food(QObject *parent) : QObject(parent)
{
}

Food* Food::generateRandomFood(int gameWidth, int gameHeight, int cellSize)
{
    Food *food = nullptr;

    int randomType = QRandomGenerator::global()->bounded(4); // Assuming you have 4 types of food
    switch (randomType) {
    case 0:
        food = new Food();
        break;
    case 1:
        food = new SpeedFood();
        break;
    case 2:
        food = new SlowFood();
        break;
    case 3:
        food = new TeleportFood();
        break;
    }

    // Set the position of the generated food
    food->setPosition(QPoint(QRandomGenerator::global()->bounded(gameWidth / cellSize),
                             QRandomGenerator::global()->bounded(gameHeight / cellSize)));

    return food;
    return food;
}

bool Food::checkCollision(const QPoint &snakeHead, int gameWidth, int gameHeight, int cellSize) const
{
    // Check if the food position collides with the snake's head or with the game boundaries
    if (m_position == snakeHead ||
        m_position.x() < 0 || m_position.x() >= (gameWidth / cellSize) ||
        m_position.y() < 0 || m_position.y() >= (gameHeight / cellSize)) {
        return true;
    }
    return false;
}
