#include <QApplication>
#include <QDebug>

#include "mainwindow.h"
#include "stringcalculator.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();


    StringCalculator::setup();
    double value = StringCalculator::calculateCharVector(StringCalculator::convertToVector("1/5"));
    qDebug() << value << '\n';

    return 0;
    //return a.exec();
}
