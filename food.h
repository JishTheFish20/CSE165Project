// Food.h
#ifndef FOOD_H
#define FOOD_H

#include <QObject>
#include <QPoint>
#include <QRandomGenerator>
#include <qdebug.h>

class Food : public QObject
{
    Q_OBJECT
public:
    enum Type {
        Normal,
        SpeedBoost,
        SnailEffect,
        TeleportFruit
    };

    explicit Food(QObject *parent = nullptr);

    static Food* generateRandomFood(int gameWidth, int gameHeight, int cellSize);

    virtual Type type() const { return Normal; }
    virtual void setType(Type type) { m_type = type; }

    virtual QPoint position() const { return m_position; }
    virtual void setPosition(const QPoint &position) { m_position = position; }
    virtual QString getName(){ return "NormalFood";}

    virtual void applyEffect() const{}


    bool checkCollision(const QPoint &snakeHead, int gameWidth, int gameHeight, int cellSize) const;

private:
    Type m_type;
    QPoint m_position;
};

#endif // FOOD_H
