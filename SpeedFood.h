#ifndef SPEEDFOOD_H
#define SPEEDFOOD_H

#include "food.h"


class SpeedFood : public Food
{
    Q_OBJECT
public:
    SpeedFood(QObject *parent = nullptr) : Food(parent) {}

    Type type() const override { return SpeedBoost; }
    void setType(Type type) override {} // Overridden to prevent changing type


    QString getName() override{
        //qDebug() << "Speed Food getName() called";
        return QString("SpeedFood");
    }

};

#endif // SPEEDFOOD_H
