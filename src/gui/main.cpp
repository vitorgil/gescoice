#include "MainWindow.h"
#include <QApplication>

#include <iostream>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w(a.focusWidget());
    w.show();

    return a.exec();
}
