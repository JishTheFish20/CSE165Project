#ifndef SLOWFOOD_H
#define SLOWFOOD_H

#include "food.h"

class SlowFood : public Food
{
    Q_OBJECT
public:
    SlowFood(QObject *parent = nullptr) : Food(parent) {}

    Type type() const override { return SnailEffect; }
    void setType(Type type) override {} // Overridden to prevent changing type

    void applyEffect() const override {
        // Emit signal to notify about speed boost effect
        emit speedBoostApplied();
    }

    QString getName() override{
        return "SlowFood";
    }

signals:
    void speedBoostApplied() const; // Signal emitted when speed boost effect is applied (const signal)
};

#endif // SLOWFOOD_H
