#include "mainwindow.h"
#include "Game.hpp"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    //w.playGame();

    return a.exec();
}
