#ifndef STRINGCALCULATOR_H
#define STRINGCALCULATOR_H

#include <QApplication>

#include "expressionelement.h"

class StringCalculator
{

public:
    static const bool DEBUG = false;


public:
    static void setup();
    static int subMain();
    static double calculateCharVector(QVector<char>);
    static ExpressionElement calculateList(QVector<ExpressionElement>);
    static QVector<ExpressionElement> generateVector(QVector<char> inputVector);
    static QVector<char> convertToVector(QString);
};

#endif // STRINGCALCULATOR_H
