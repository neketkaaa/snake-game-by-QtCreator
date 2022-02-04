#include "block.h"
#include <QPainter>

Block::Block()
{

}

Block::Block(int a, int b)
    :x(a), y(b)
{

}

int Block::getX()
{
    return x;
}

void Block::setX(int newX)
{
    x = newX;
}

int Block::getY()
{
    return y;
}

void Block::setY(int newY)
{
    y = newY;
}

void Block::drawBlocks(QPainter *painter)
{
    QPen dark(Qt::black, 2);
    painter->setPen(dark);
    painter->drawRect(x, y, size, size);
}
