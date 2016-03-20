#include <QApplication>
#include <QDebug>
#include <stdio.h>
#include <math.h>

#include "mainwindow.h"
#include "expressionelement.h"
#include "stringcalculator.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //MainWindow w;
    //w.show();

    try
    {
        StringCalculator::setup();
        ExpressionElement::useDegrees(true);
        double value = 0;

        value = StringCalculator::calculateQStringInput(QString("90[+]10"));
        qDebug() << "Test1: " << (abs(100-value) < 0.001);
        value = StringCalculator::calculateQStringInput(QString("10[+]90"));
        qDebug() << "Test2: " << (abs(100-value) < 0.001);
        value = StringCalculator::calculateQStringInput(QString("90[-]10"));
        qDebug() << "Test3: " << (abs(80-value) < 0.001);
        value = StringCalculator::calculateQStringInput(QString("10[-]90"));
        qDebug() << "Test4: " << (abs(-80-value) < 0.001);
        value = StringCalculator::calculateQStringInput(QString("10[*]90"));
        qDebug() << "Test5: " << (abs(900-value) < 0.001);
        value = StringCalculator::calculateQStringInput(QString("10[/]90"));
        qDebug() << "Test6: " << (abs((1/9)-value) < 0.001);
        value = StringCalculator::calculateQStringInput(QString("9[*]10[/]90"));
        qDebug() << "Test7: " << (abs(1-value) < 0.001);
        value = StringCalculator::calculateQStringInput(QString("10[+]10[*]2"));
        qDebug() << "Test8: " << (abs(30-value) < 0.001);
        value = StringCalculator::calculateQStringInput(QString("5[*]10[+]10[*]2"));
        qDebug() << "Test9: " << (abs(70-value) < 0.001);
        value = StringCalculator::calculateQStringInput(QString("[sin]30[+]10[*]2"));
        qDebug() << "Test10: " << (abs(20.5-value) < 0.001);
        value = StringCalculator::calculateQStringInput(QString("2.5[+][sin]30"));
        qDebug() << "Test11: " << (abs(3-value) < 0.001);
        value = StringCalculator::calculateQStringInput(QString("(30[+]15[/]3)"));
        qDebug() << "Test12: " << (abs(35-value) < 0.001);
        value = StringCalculator::calculateQStringInput(QString("45(10)"));
        qDebug() << "Test13: " << (abs(450-value) < 0.001);
        value = StringCalculator::calculateQStringInput(QString("(45)10"));
        qDebug() << "Test14: " << (abs(450-value) < 0.001);
        value = StringCalculator::calculateQStringInput(QString("10+(10)"));
        qDebug() << "Test15: " << (abs(20-value) < 0.001);

        // ExpressionElement tests

        // Setup the operation map
        //ExpressionElement::setupOperationMap();
        //ExpressionElement::useDegrees(false);
        //ExpressionElement num1 = ExpressionElement(1);
        //ExpressionElement num2 = ExpressionElement(-30);
        //qDebug() << ExpressionElement("[sin]").calc(num1, num2).toString();

    }
    catch (int e)
    {
        qDebug() << "There was an error: Error Num" << e << '\n';
    }

    return 0;
    //return a.exec();
}
