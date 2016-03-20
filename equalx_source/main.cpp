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

    /*
    try
    {
        StringCalculator::setup();
        ExpressionElement::useDegrees(true);
        double value = 0;


        value = StringCalculator::calculateQStringInput(QString("90[+]10"));
        qDebug() << "Test1: " << (abs(100-value) < 0.0000001);
        value = StringCalculator::calculateQStringInput(QString("10[+]90"));
        qDebug() << "Test2: " << (abs(100-value) < 0.0000001);
        value = StringCalculator::calculateQStringInput(QString("90[-]10"));
        qDebug() << "Test3: " << (abs(80-value) < 0.0000001);
        value = StringCalculator::calculateQStringInput(QString("10[-]90"));
        qDebug() << "Test4: " << (abs(-80-value) < 0.0000001);
        value = StringCalculator::calculateQStringInput(QString("10[*]90"));
        qDebug() << "Test5: " << (abs(900-value) < 0.0000001);
        value = StringCalculator::calculateQStringInput(QString("10[/]90"));
        qDebug() << "Test6: " << (abs((1/9)-value) < 0.0000001);
        value = StringCalculator::calculateQStringInput(QString("9[*]10[/]90"));
        qDebug() << "Test7: " << (abs(1-value) < 0.0000001);
        value = StringCalculator::calculateQStringInput(QString("10[+]10[*]2"));
        qDebug() << "Test8: " << (abs(30-value) < 0.0000001);
        value = StringCalculator::calculateQStringInput(QString("5[*]10[+]10[*]2"));
        qDebug() << "Test9: " << (abs(70-value) < 0.0000001);
        value = StringCalculator::calculateQStringInput(QString("[sin]30[+]10[*]2"));
        qDebug() << "Test10: " << (abs(20.5-value) < 0.0000001);
        value = StringCalculator::calculateQStringInput(QString("2.5[+][sin]30"));
        qDebug() << "Test11: " << (abs(3-value) < 0.0000001);
        value = StringCalculator::calculateQStringInput(QString("(30[+]15[/]3)"));
        qDebug() << "Test12: " << (abs(35-value) < 0.0000001);
        value = StringCalculator::calculateQStringInput(QString("45(10)"));
        qDebug() << "Test13: " << (abs(450-value) < 0.0000001);
        value = StringCalculator::calculateQStringInput(QString("(45)10"));
        qDebug() << "Test14: " << (abs(450-value) < 0.00001);
        value = StringCalculator::calculateQStringInput(QString("10[+](10)"));
        qDebug() << "Test15: " << (abs(20-value) < 0.0000001);
        value = StringCalculator::calculateQStringInput(QString("[sin](45[+]45)"));
        qDebug() << "Test16: " << (abs(1-value) < 0.0000001);
        value = StringCalculator::calculateQStringInput(QString("((5))"));
        qDebug() << "Test17: " << (abs(5-value) < 0.0000001);
        value = StringCalculator::calculateQStringInput(QString("((8[+]0[-]5))"));
        qDebug() << "Test18: " << (abs(3-value) < 0.0000001);
        value = StringCalculator::calculateQStringInput(QString("[cos](45[+]45)"));
        qDebug() << "Test19: " << (abs(0-value) < 0.0000001);
        value = StringCalculator::calculateQStringInput(QString("(17[+][cos](45[+]45)[+][sin](90))[/]18"));
        qDebug() << "Test20: " << (abs(1-value) < 0.0000001);
        value = StringCalculator::calculateQStringInput(QString("[tan](45)"));
        qDebug() << "Test21: " << (abs(1-value) < 0.0000001);
        value = StringCalculator::calculateQStringInput(QString("([sin](45))[^]2"));
        qDebug() << "Test22: " << (abs(0.5-value) < 0.0000001);
        value = StringCalculator::calculateQStringInput(QString("4[pi]4"));
        qDebug() << "Test23: " << (abs(16*M_PI-value) < 0.0000001);
        value = StringCalculator::calculateQStringInput(QString("[pi]"));
        qDebug() << "Test24: " << (abs(M_PI-value) < 0.0000001);
        value = StringCalculator::calculateQStringInput(QString("[e]"));
        qDebug() << "Test25: " << (abs(M_E-value) < 0.0000001);
        value = StringCalculator::calculateQStringInput(QString("[pi][e]"));
        qDebug() << "Test26: " << (abs(M_PI*M_E-value) < 0.0000001);
        value = StringCalculator::calculateQStringInput(QString("([e])[^]([pi])"));
        qDebug() << "Test27: " << (abs(23.14069263-value) < 0.0000001);

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
    */
    return 0;
    //return a.exec();
}
