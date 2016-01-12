#ifndef EXPRESSIONELEMENT_H
#define EXPRESSIONELEMENT_H

#include <QApplication>

#include "operation.h"

class ExpressionElement
{
    public:
        bool isNumber = true;
        Operation::Enum op = Operation::none;
        double value = 0;

    public:
        ExpressionElement();
        ExpressionElement(double);
        ExpressionElement(char);
        ExpressionElement(QVector<char>);
        QString toString();
        double calc(ExpressionElement, ExpressionElement);

    private:
        void initA(char);
};

#endif // EXPRESSIONELEMET_H
