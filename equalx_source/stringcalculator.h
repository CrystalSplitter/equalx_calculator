#ifndef STRINGCALCULATOR_H
#define STRINGCALCULATOR_H

#include <QApplication>
#include <QDebug>
#include <math.h>

#include "expressionelement.h"

class StringCalculator
{
    // Private fields
private:
    static QVector<QString> OP_ORDER;

    // Public methods
public:
    static void setup();
    static double calculateQStringInput(QString input);
    static void useDegrees(bool y);

    // Private methods
private:
    StringCalculator(); // Make the instructor impossible to use.
    static ExpressionElement calculateVectorInput(QVector<ExpressionElement> input);
    static QVector<ExpressionElement> genExpressionElements(QString input);

};

#endif // STRINGCALCULATOR_H
