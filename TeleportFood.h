#ifndef TELEPORTFOOD_H
#define TELEPORTFOOD_H

#include "food.h"

class TeleportFood : public Food
{
    Q_OBJECT
public:
    TeleportFood(QObject *parent = nullptr) : Food(parent) {}

    Type type() const override { return TeleportFruit; }
    void setType(Type type) override {} // Overridden to prevent changing type

    void applyEffect() const override {
        // Emit signal to notify about speed boost effect
        emit speedBoostApplied();
    }

    QString getName() override{
        return "TeleportFood";
    }

signals:
    void speedBoostApplied() const; // Signal emitted when speed boost effect is applied (const signal)
};

#endif // TELEPORTFOOD_H
