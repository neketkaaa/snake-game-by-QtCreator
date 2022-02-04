#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMouseEvent>
#include <QDebug>
#include <QPainter>
#include <QLabel>
#include <QKeyEvent>
#include <QTimer>
#include "snake.h"
#include <QFontMetrics>
#include <QMessageBox>
#include <QRandomGenerator>
#include <cstdlib>
#include <iostream>
#include <ctime>
#include "block.h"
#include "food.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    initGame();
    QTimer *timer = new QTimer();
    connect(timer, SIGNAL(timeout()), this, SLOT(update()));
    timer->start(400);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::paintEvent(QPaintEvent *)
{
    QPainter painter(this);

// Рисовка фонового поля
    QBrush grayBrush(Qt::darkGray);
    painter.setBrush(grayBrush);
    painter.drawRect(-1, -1, this->width()+1, this->height()+1);

    QPen grayPencil(Qt::lightGray, 1);
    painter.setPen(grayPencil);
    for (int i = 1; i < fieldSize; i++){
        painter.drawLine(i*this->width()/fieldSize, 0, i*this->width()/fieldSize, this->height());
        painter.drawLine(0, i*this->height()/fieldSize, this->width(), i*this->height()/fieldSize);
    }

// Рисовка змеи
    QBrush brush_1(Qt::darkGreen);
    painter.setBrush(brush_1);
    bodyParts[0]->drawHead(&painter, left, right, up, down);

    QBrush brush_2(Qt::green);
    painter.setBrush(brush_2);
    for (int i = 1; i < bodyParts.size(); i++){
        bodyParts[i]->drawSnake(&painter);
    }

    checkBlocks();

// Рисовка блоков
    QBrush black(Qt::black);
    painter.setBrush(black);
    for (int i = 0; i < blocks.size(); i++){
        blocks[i]->drawBlocks(&painter);
    }

    checkFood();

// Рисовка еды
    QBrush red(Qt::red);
   painter.setBrush(red);
   for (int i = 0; i<allFood.size(); i++){
       allFood[i]->drawFood(&painter);
   }
}

// Проверка нажатой клавиши
void MainWindow::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Up && !down)
    {
        left = false;
        right = false;
        up = true;
    }

    if (event->key() == Qt::Key_Down && !up && isStart)  // изначально не может быть нажата клавиша "down"
    {
        left = false;
        right = false;
        down = true;
    }

    if (event->key() == Qt::Key_Left && !right)
    {
        left = true;
        down = false;
        up = false;
    }

    if (event->key() == Qt::Key_Right && !left)
    {
        down = false;
        right = true;
        up = false;
    }

    isStart = true;
}

// Стартовая инициализация игры
void MainWindow::initGame()
{
    for (int i = 0;i < currentLength; i++) {
        Snake *mainSnake = nullptr;
        mainSnake = new Snake(startXY, startXY+size*i);
        bodyParts.append(mainSnake);
    }

    up = false;                                               // изначально змейка стоит на месте и глаза закрыты
    left = false;
    right = false;
    down = false;

    for (int i = 0; i<blocksNum; i++){                        // если блок создан "на" змейке при старте
        int rand_x = takeRandom();
        int rand_y = takeRandom();

    for (int j=0; j<currentLength; j++){
        if (rand_x == startXY  && rand_y == startXY + size * j){
            rand_x = takeRandom();
            rand_y = takeRandom();
        }
    }

        Block *block = nullptr;
        block = new Block(rand_x, rand_y);
        blocks.append(block);
    }

    for (int i = 0; i < foodNum; i++){                        // если еда создана "на" змейке при старте
        int rand_x = takeRandom();
        int rand_y = takeRandom();

        for (int j=0; j<currentLength; j++){
            if (rand_x == startXY  && rand_y == startXY + size * j){
                rand_x = takeRandom();
                rand_y = takeRandom();
            }
        }

        Food *food = nullptr;
        food = new Food(rand_x, rand_y);
        allFood.append(food);
    }

    checkFood();
    checkBlocks();
    repaint();
}

// Увеличение змейки
void MainWindow::initSnake()
{
    Snake *newPart = nullptr;
    newPart = new Snake(bodyParts[currentLength-1]->getX(), bodyParts[currentLength-1]->getY());
    bodyParts.append(newPart);
    currentLength++;
}

// Генерация рандомного числа
int MainWindow::takeRandom()
{
    int rand = QRandomGenerator::global()->bounded(0, 10000000) % fieldSize * size;
    return rand;
}

// Проверка случаев проигрыша
void MainWindow::gameOver()
{
    for (int i=1; i<bodyParts.size(); i++){                 // змейка укусила сама себя
        if (bodyParts[0]->getX() == bodyParts[i]->getX() && bodyParts[0]->getY() == bodyParts[i]->getY()){
            endOfGame();
        }
    }

    repaint();
                                                           // змейка вышла за поле
    if (bodyParts[0]->getX() < 0 || bodyParts[0]->getX() >= this->width() || bodyParts[0]->getY() < 0 || bodyParts[0]->getY() >= this->height()) {
       endOfGame();
    }

    for (int i = 0; i < blocks.size(); i++){               // змейка столкнулась с блоком
        if(abs(bodyParts[0]->getX() - blocks[i]->getX()) <= size-1 && abs(bodyParts[0]->getY() - blocks[i]->getY()) <= size-1){
         endOfGame();
        }
    }

    repaint();
}

// Оповещение о конце игры и закрытие окна
void MainWindow::endOfGame()
{
    QMessageBox box(this);
    box.setWindowTitle("# # #");
    box.setText("GAME OVER!");
    box.exec();

    QApplication::quit();
}

// Проверка различных "неприятных" ситуаций с появлением еды
void MainWindow::checkFood()
{
    for (int i = 0; i < foodNum; i++){              // если еда с блоком "делят" одну клетку на двоих
        for (int j = 0; j < blocksNum; j++){
            if (allFood[i]->getX() == blocks[j]->getX() && allFood[i]->getY() == blocks[j]->getY()){
                allFood[i]->setX(takeRandom());
            }
        }
    }

    for (int i = 0; i < foodNum; i++){              // если новая еда появляется "под" змейкой
        for (int j = 0; j <currentLength-1; j++){
            if (allFood[i]->getX() == bodyParts[j]->getX() && allFood[i]->getY() == bodyParts[j]->getY()){
                allFood[i]->setX(takeRandom());
            }
        }
    }

    for (int i = 0; i < foodNum-1; i++){            // если две порции еды "делят" одну клетку на двоих
        for (int j = i+1; j<foodNum; j++){
            if (allFood[i]->getX() == allFood[j]->getX() && allFood[i]->getY() == allFood[j]->getY())
            {
                allFood[i]->setX(takeRandom());
            }
        }
    }

}

// Проверка различных "неприятных" ситуаций с появлением блоков
void MainWindow::checkBlocks()
{
    for (int i = 0; i < blocksNum-1; i++){                  // если два блока "делят" одну клетку на двоих
        for (int j = i+1; j<blocksNum; j++){
            if (blocks[i]->getX() == blocks[j]->getX() && blocks[i]->getY() == blocks[j]->getY())
            {
                blocks[i]->setX(takeRandom());
            }
        }
    }

    for (int i = 0; i < foodNum; i++){              // если еда с блоком "делят" одну клетку на двоих
        for (int j = 0; j < blocksNum; j++){
            if (allFood[i]->getX() == blocks[j]->getX() && allFood[i]->getY() == blocks[j]->getY()){
                allFood[i]->setX(takeRandom());
            }
        }
    }
}



// Обновление "текущей ситуации" в игре
void MainWindow::update()
{
    gameOver(); // проверка текущей ситуации на проигрыш
    repaint();

// Передвижение
    if (up || down || left || right){
        for(int i = bodyParts.size()-1;i > 0; i--){
            bodyParts[i]->setX(bodyParts[i-1]->getX());
            bodyParts[i]->setY(bodyParts[i-1]->getY());
            repaint();
        }
    }

    if (left)
        bodyParts[0]->setX(bodyParts[0]->getX()-size);
    if (right)
        bodyParts[0]->setX(bodyParts[0]->getX()+size);
    if (up)
        bodyParts[0]->setY(bodyParts[0]->getY()-size);
    if (down)
        bodyParts[0]->setY(bodyParts[0]->getY()+size);
//

    for (int i = 0; i<allFood.size(); i++)                         // змейка съела еду
    {
        if(bodyParts[0]->getX() == allFood[i]->getX() && bodyParts[0]->getY() == allFood[i]->getY())
        {
            allFood[i]->setX(takeRandom());
            allFood[i]->setY(takeRandom());
            initSnake();
            checkFood();
            repaint();
        }
    }

    repaint();
}
