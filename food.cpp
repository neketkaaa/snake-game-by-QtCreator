#include "food.h"
#include <QPainter>

Food::Food()
{

}

Food::Food(int a, int b)
    :x(a),y(b)
{

}

int Food::getX()
{
    return x;
}

void Food::setX(int newX)
{
    x = newX;
}

int Food::getY()
{
    return y;
}

void Food::setY(int newY)
{
    y = newY;
}

void Food::drawFood(QPainter *painter)
{
    QPen yellow(Qt::yellow, 1);
    painter->setPen(yellow);
    painter->drawRect(x, y, size, size);
}
