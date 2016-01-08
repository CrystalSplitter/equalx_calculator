#ifndef STRINGCALCULATOR_H
#define STRINGCALCULATOR_H

#include <QApplication>

#include "expressionelement.h"

class StringCalculator
{

public:
    static const bool DEBUG = false;


public:
    static int subMain();
    static double calculateCharVector(QVector<char>);
    static QVector<ExpressionElement> generateList(QVector<char>);
};

#endif // STRINGCALCULATOR_H
