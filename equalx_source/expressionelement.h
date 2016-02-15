#ifndef EXPRESSIONELEMENT_H
#define EXPRESSIONELEMENT_H

#include <QApplication>
#include "utilities.h"
#include "operation.h"

class ExpressionElement
{
    public:
        bool isNumber = true;
        QString op = "None";
        double value = 0;

    public:
        ExpressionElement();
        ExpressionElement(QString);
        ExpressionElement(double);
        QString toString();
        ExpressionElement calc(ExpressionElement, ExpressionElement);
    private:
        bool setOperation(QString);
};

#endif // EXPRESSIONELEMET_H
