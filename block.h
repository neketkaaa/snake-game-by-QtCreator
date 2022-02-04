#ifndef BLOCK_H
#define BLOCK_H


class Block
{
public:
    Block();
    Block(int a, int b);

    int getX();
    void setX(int newX);

    int getY();
    void setY(int newY);

    void drawBlocks(class QPainter *painter);
private:
    int x, y;
    static const int size = 24;
};

#endif // BLOCK_H
