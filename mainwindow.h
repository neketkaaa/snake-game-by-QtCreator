#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<QVector>
class Snake;
class Block;
class Food;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public slots:
    void update();

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void paintEvent(QPaintEvent *);
    void keyPressEvent(QKeyEvent *event);
    void initGame();
    void initSnake();
    int takeRandom();
    void gameOver();
    void endOfGame();
    void checkFood();
    void checkBlocks();

private:
    Ui::MainWindow *ui;
    QVector <Snake*> bodyParts; // "части тела" змеи
    static const int size = 24;
    bool left;
    bool right;
    bool up;
    bool down;
    int currentLength = 3;
    QVector<Block*> blocks; // блоки на поле
    QVector<Food*> allFood; // еда на поле
    bool isStart = false;
    static const int fieldSize = 25;
    int startXY = 312; // стартовые координаты расположения
    int blocksNum = 10;
    int foodNum = 5;
};
#endif // MAINWINDOW_H
