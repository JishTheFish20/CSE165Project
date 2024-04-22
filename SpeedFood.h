#ifndef SPEEDFOOD_H
#define SPEEDFOOD_H

#include "food.h"

class SpeedFood : public Food
{
public:
    SpeedFood(QObject *parent = nullptr) : Food(parent) {}

    Type type() const override { return SpeedBoost; }
    void setType(Type type) override {} // Overridden to prevent changing type

    void applyEffect(Snake &snake) const {
        int currentSpeed = snake.getSnakeSpeed();
        int newSpeed = currentSpeed - 20; // Decrease interval by 20 milliseconds
        snake.setSnakeSpeed(newSpeed);
    }
};

#endif // SPEEDFOOD_H
