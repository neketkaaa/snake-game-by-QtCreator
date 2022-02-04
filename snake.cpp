#include "snake.h"
#include <QPainter>
#include <QRandomGenerator64>

Snake::Snake()
{

}

Snake::Snake(int a, int b)
    :x(a),y(b)
{
}

int Snake::getX()
{
    return x;
}


void Snake::setX(int newX)
{
    x = newX;
}

int Snake::getY()
{
    return y;
}

void Snake::setY(int newY)
{
    y = newY;
}

void Snake::drawSnake(QPainter *painter)
{
    QPen darkGreen(Qt::darkGreen, 2);
    painter->setPen(darkGreen);
    painter->drawRect(x, y, size, size);
}

void Snake::drawHead(QPainter *painter, bool left, bool right, bool up, bool down)
{
    QPen darkGreen(Qt::darkGreen, 2);
    painter->setPen(darkGreen);
    painter->drawRect(x, y, size, size);
    QPen white(Qt::white, 1);
    painter->setPen(white);

    if(left)
    {
    painter->drawText(x, y + 21, "●");
    painter->drawText(x, y + 9, "●");
    }
    if(right)
    {
    painter->drawText(x + 17, y + 21, "●");
    painter->drawText(x+17, y + 9, "●");
    }
    if(up)
    {
    painter->drawText(x+3, y+7, "●");
    painter->drawText(x+16, y+7, "●");
    }
    if(down)
    {
    painter->drawText(x+3, y+21, "●");
    painter->drawText(x+16, y+21, "●");
    }
}

