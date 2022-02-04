#ifndef SNAKE_H
#define SNAKE_H

class Snake
{
public:
    Snake();
    Snake(int a, int b);

    int getX();
    void setX(int newX);

    int getY();
    void setY(int newY);

    void drawSnake(class QPainter *painter);
    void drawHead(class QPainter *painter, bool left, bool right, bool up, bool down);
private:
    int x, y;
    static const int size = 24;
};

#endif // SNAKE_H
