#include <QApplication>

#include "mainwindow.h"
#include "stringcalculator.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    StringCalculator::subMain();

    return 0;
    //return a.exec();
}
