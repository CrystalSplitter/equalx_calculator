#include <QApplication>
#include <QDebug>
#include <stdio.h>
#include <math.h>

#include "mainwindow.h"
#include "expressionelement.h"
#include "stringcalculator.h"
#include "unittester.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // Setup the calculator so it can
    // actually parse stuff correctly.
    StringCalculator::setup();
    StringCalculator::useDegrees(true);

    // Create a unit tester of accuracy of magnitude 10
    UnitTester tester = UnitTester(8, false);

    //MainWindow w;
    //w.show();

    try
    {
        tester.assertEqual("1", StringCalculator::calculateQStringInput(QString("90[+]10")), 100);
        tester.assertEqual("2", StringCalculator::calculateQStringInput(QString("10[+]90")), 100);
        tester.assertEqual("3", StringCalculator::calculateQStringInput(QString("90[-]10")), 80);
        tester.assertEqual("4", StringCalculator::calculateQStringInput(QString("10[-]90")), -80);
        tester.assertEqual("5", StringCalculator::calculateQStringInput(QString("10[*]90")), 900);
        tester.assertEqual("6", StringCalculator::calculateQStringInput(QString("10[/]90")), 1/(double)9);
        tester.assertEqual("7", StringCalculator::calculateQStringInput(QString("9[*]10[/]90")), 1);
        tester.assertEqual("8", StringCalculator::calculateQStringInput(QString("10[+]10[*]2")), 30);
        tester.assertEqual("9", StringCalculator::calculateQStringInput(QString("5[*]10[+]10[*]2")), 70);
        tester.assertEqual("10", StringCalculator::calculateQStringInput(QString("[sin]30[+]10[*]2")), 20.5);
        tester.assertEqual("11", StringCalculator::calculateQStringInput(QString("2.5[+][sin]30")), 3);
        tester.assertEqual("12", StringCalculator::calculateQStringInput(QString("(30[+]15[/]3)")), 35);
        tester.assertEqual("13", StringCalculator::calculateQStringInput(QString("45(10)")), 450);
        tester.assertEqual("14", StringCalculator::calculateQStringInput(QString("(45)10")), 450);
        tester.assertEqual("15", StringCalculator::calculateQStringInput(QString("10[+](10)")), 20);
        tester.assertEqual("16", StringCalculator::calculateQStringInput(QString("[sin](45[+]45)")), 1);
        tester.assertEqual("17", StringCalculator::calculateQStringInput(QString("((5))")), 5);
        tester.assertEqual("18", StringCalculator::calculateQStringInput(QString("((8[+]0[-]5))")), 3);
        tester.assertEqual("19", StringCalculator::calculateQStringInput(QString("[cos](45[+]45)")), 0);
        tester.assertEqual("20", StringCalculator::calculateQStringInput(QString("(17[+][cos](45[+]45)[+][sin](90))[/]18")), 1);
        tester.assertEqual("21", StringCalculator::calculateQStringInput(QString("[tan](45)")), 1.0);
        tester.assertEqual("22", StringCalculator::calculateQStringInput(QString("([sin](45))[^]2")), 0.5);
        tester.assertEqual("23", StringCalculator::calculateQStringInput(QString("4[pi]4")), 16*M_PI);
        tester.assertEqual("24", StringCalculator::calculateQStringInput(QString("[pi]")), M_PI);
        tester.assertEqual("25", StringCalculator::calculateQStringInput(QString("[e]")), M_E);
        tester.assertEqual("26", StringCalculator::calculateQStringInput(QString("[pi][e]")), M_PI*M_E);
        tester.assertEqual("27", StringCalculator::calculateQStringInput(QString("([e])[^]([pi])")), 23.1406926328);
        tester.assertEqual("28", StringCalculator::calculateQStringInput(QString("[+]7")), 7);

        StringCalculator::useDegrees(false);
        tester.assertEqual("29", StringCalculator::calculateQStringInput(QString("[cos]([pi])")), -1);
        tester.assertEqual("30", StringCalculator::calculateQStringInput(QString("[sin](3[*][pi][/]2)")), -1);
        tester.assertEqual("31", StringCalculator::calculateQStringInput(QString("[tan]([pi][/]4)")), 1);

        StringCalculator::useDegrees(true);
        tester.assertEqual("32", StringCalculator::calculateQStringInput(QString("7[!]")), 5040);
        tester.assertEqual("33", StringCalculator::calculateQStringInput(QString("(6)[!]")), 720);

        try {StringCalculator::calculateQStringInput(QString("[e][!]")); qDebug() << "Test34: " << false;}
        catch (int e) {}
        try {StringCalculator::calculateQStringInput(QString("([-]1)[!]")); qDebug() << "Test34: " << false;}
        catch (int e) {}

        tester.assertEqual("36", StringCalculator::calculateQStringInput(QString("[-](1[!])")), -1);
        tester.assertEqual("37", StringCalculator::calculateQStringInput(QString("(0[!])")), 1);
        tester.assertEqual("38", StringCalculator::calculateQStringInput(QString("5[P]3")), 60);
        tester.assertEqual("39", StringCalculator::calculateQStringInput(QString("10[P]1")), 10);
        tester.assertEqual("40", StringCalculator::calculateQStringInput(QString("10[P]10")), 3628800);
        tester.assertEqual("41", StringCalculator::calculateQStringInput(QString("7[P]6")), 5040);
        tester.assertEqual("42", StringCalculator::calculateQStringInput(QString("7[P]0")), 1);

        try {StringCalculator::calculateQStringInput(QString("3[P]5")); qDebug() << "Test42: " << false;}
        catch (int e) {}

        tester.assertEqual("44", StringCalculator::calculateQStringInput(QString("7[C]6")), 7);
        tester.assertEqual("45", StringCalculator::calculateQStringInput(QString("7[C]1")), 7);
        tester.assertEqual("46", StringCalculator::calculateQStringInput(QString("9[C]0")), 1);
        tester.assertEqual("47", StringCalculator::calculateQStringInput(QString("9[C]9")), 1);
        tester.assertEqual("48", StringCalculator::calculateQStringInput(QString("9[C]5")), 126);
        tester.assertEqual("49", StringCalculator::calculateQStringInput(QString("36[C]4")), 58905);
        tester.assertEqual("50", StringCalculator::calculateQStringInput(QString("15[!]")), 1.307674368*pow(10,12));
        tester.assertEqual("51", StringCalculator::calculateQStringInput(QString("20[!]")), 2.432902008*pow(10,18));

        tester.assertEqual("52", StringCalculator::calculateQStringInput(QString("[ln][e]")), 1);
        tester.assertEqual("53", StringCalculator::calculateQStringInput(QString("[ln]5.5")), 1.704748);
        tester.assertEqual("54", StringCalculator::calculateQStringInput(QString("[ln]1")), 0);
        tester.assertEqual("55", StringCalculator::calculateQStringInput(QString("[log]10")), 1);
        tester.assertEqual("56", StringCalculator::calculateQStringInput(QString("[log]1")), 0);
        tester.assertEqual("57", StringCalculator::calculateQStringInput(QString("[log]100")), 2);
        tester.assertEqual("58", StringCalculator::calculateQStringInput(QString("[log]10000")), 4);
        tester.assertEqual("59", StringCalculator::calculateQStringInput(QString("[log]87")), 1.939519253);
        tester.assertEqual("60", StringCalculator::calculateQStringInput(QString("[asin]0")), 0);
        tester.assertEqual("61", StringCalculator::calculateQStringInput(QString("[acos]0")), 90);
        tester.assertEqual("62", StringCalculator::calculateQStringInput(QString("[asin]1")), 90);
        tester.assertEqual("63", StringCalculator::calculateQStringInput(QString("[asin]-1")), -90);
        tester.assertEqual("64", StringCalculator::calculateQStringInput(QString("7[asin](-1)")), -90*7);
        tester.assertEqual("65", StringCalculator::calculateQStringInput(QString("10[atan](0)")), 0);
        tester.assertEqual("66", StringCalculator::calculateQStringInput(QString("10[atan](1000)")), 899.4270424);
        tester.assertEqual("67", StringCalculator::calculateQStringInput(QString("10[atan](-1000)")), -899.4270424);
        tester.assertEqual("68", StringCalculator::calculateQStringInput(QString("[atan](-1)")), -45);
        tester.assertEqual("69", StringCalculator::calculateQStringInput(QString("[atan](1)")), 45);

        StringCalculator::useDegrees(false);
        tester.assertEqual("70", StringCalculator::calculateQStringInput(QString("[atan](1)")), M_PI/4);
        tester.assertEqual("71", StringCalculator::calculateQStringInput(QString("[asin](1)")), M_PI/2);
        tester.assertEqual("72", StringCalculator::calculateQStringInput(QString("[acos](1)")), 0);
        tester.assertEqual("73", StringCalculator::calculateQStringInput(QString("[asin](0.5)")), M_PI/6);
        tester.assertEqual("74", StringCalculator::calculateQStringInput(QString("[acos](0.5)")), M_PI/3);
        tester.assertEqual("75", StringCalculator::calculateQStringInput(QString("[atan](25")), 1.53081764);

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
