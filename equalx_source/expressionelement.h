#ifndef EXPRESSIONELEMENT_H
#define EXPRESSIONELEMENT_H

#include "QApplication"
#include <QDebug>
#include <math.h>

class ExpressionElement
{
    public:
        bool isNumber = true;
        QString op = "None";
        double value = 0;
    private:
        static std::map<QString,int> opToIntMap;
        static bool useDeg;
        static double conversion;

    public:
        ExpressionElement();
        ExpressionElement(QString);
        ExpressionElement(double);
        QString toString() const;
        QVector<ExpressionElement> calc(ExpressionElement, ExpressionElement);
        static void setupOperationMap();
        static void useDegrees(bool);
    private:
        bool setOperation(QString);
        static double factorial(double);

};

#endif // EXPRESSIONELEMET_H
