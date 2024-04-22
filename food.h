#ifndef FOOD_H
#define FOOD_H

#include <QObject>
#include <QPoint>
#include <QPainter>
#include "Snake.h"

class Food : public QObject
{
    Q_OBJECT
public:
    enum Type {
        Normal,
        SpeedBoost, // New type for speed boost food
        ColorChange // New type for color change food
    };

    explicit Food(QObject *parent = nullptr);

    virtual Type type() const { return m_type; } // Made virtual for polymorphism
    virtual void setType(Type type) { m_type = type; } // Made virtual for polymorphism

    virtual QPoint position() const { return m_position; } // Made virtual for polymorphism
    virtual void setPosition(const QPoint &position) { m_position = position; } // Made virtual for polymorphism

    virtual void applyEffect(Snake &snake) const {}
    // Virtual destructor for proper cleanup in derived classes
    virtual ~Food() {}

private:
    Type m_type;
    QPoint m_position;
};

#endif // FOOD_H
