#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.setWindowTitle("Game ''Snake''");
    w.resize(600, 600); // размер поля окна 600х600
    w.show();
    w.setFixedSize(w.geometry().width(),w.geometry().height()); // фиксация размера окна
    return a.exec();
}
