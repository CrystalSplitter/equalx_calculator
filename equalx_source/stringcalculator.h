#ifndef STRINGCALCULATOR_H
#define STRINGCALCULATOR_H

#include <QApplication>

#include "expressionelement.h"
#include "utilities.h"

class StringCalculator
{

    // Public Variables
public:
    static const bool DEBUG = false;

    // Public Methods
public:
    static void setup();
    static int subMain();
    static double calculateCharVector(QVector<char>);
    static double subExpressionSolver(QVector<char> vect, int start, int end);
    static ExpressionElement calculateList(QVector<ExpressionElement>);
    static QVector<ExpressionElement> generateVector(QVector<char> inputVector);
    static QVector<char> convertToVector(QString);

private:
    static bool vectorComparison(QVector<char>, QVector<char>);
};

#endif // STRINGCALCULATOR_H
