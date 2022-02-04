#ifndef FOOD_H
#define FOOD_H


class Food
{
public:
    Food();
    Food(int a, int b);

    int getX();
    void setX(int newX);

    int getY();
    void setY(int newY);

    void drawFood(class QPainter *painter);
private:
    int x, y;
    static const int size = 24;
};

#endif // FOOD_H
