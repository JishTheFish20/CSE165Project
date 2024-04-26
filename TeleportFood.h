#ifndef TELEPORTFOOD_H
#define TELEPORTFOOD_H

#include "food.h"
#include <QRandomGenerator>
#include <QPoint>
class TeleportFood : public Food
{
    Q_OBJECT
    QPoint newHeadPosition;

public:
    TeleportFood(QObject *parent = nullptr) : Food(parent) {}

    Type type() const override { return TeleportFruit; }
    void setType(Type type) override {} // Overridden to prevent changing type

    void applyEffect() const override {
        // Emit signal to notify about speed boost effect
        emit speedBoostApplied();
    }

    QPoint getTeleportPosition(){
        return newHeadPosition;
    }

    void setTeleportPosition(int gameWidth, int gameHeight, int cellSize){
        int x = QRandomGenerator::global()->bounded(gameWidth / cellSize);
        int y = QRandomGenerator::global()->bounded(gameHeight / cellSize);
        QPoint holder(x,y);
        newHeadPosition = holder;
    }

    QString getName() override{
        return "TeleportFood";
    }

signals:
    void speedBoostApplied() const; // Signal emitted when speed boost effect is applied (const signal)
};

#endif // TELEPORTFOOD_H
