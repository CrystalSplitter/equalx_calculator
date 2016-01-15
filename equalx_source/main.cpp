#include <QApplication>
#include <QDebug>

#include "mainwindow.h"
#include "stringcalculator.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //MainWindow w;
    //w.show();

    try
    {
        StringCalculator::setup();
        double value = StringCalculator::calculateCharVector(StringCalculator::convertToVector("77(("));
        qDebug() << value << '\n';
    }
    catch (int e)
    {
        qDebug() << "There was an error: Error Num" << e << '\n';
    }

    return 0;
    //return a.exec();
}
