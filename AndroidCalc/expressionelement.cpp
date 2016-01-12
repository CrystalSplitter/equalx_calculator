#include "expressionelement.h"
#include <stdlib.h>
#include <math.h>

ExpressionElement::ExpressionElement(QVector<QChar>a,QObject *parent) : QObject(parent)
{
        op = none;
        type = number;
        val = 0;
        bool belowDecimal = false;
        int decimalPosition = -1;
        value = 0;

        for (int i = 0; i < a.size() - 1; i++)
        {
            if (a[i] == '.')
            {
                if(belowDecimal)
                {
                    emit error();
                    continue;
                }
                else
                {
                    decimalPosition = i;
                    belowDecimal = true;
                    continue;
                }
            }
            if (!belowDecimal)
            {
                val = val * 10 + a.at(i).digitValue();
            }
            else
            {
                double neg10Pow = (double)(10*(i-decimalPosition));
                val = val + a.at(i).digitValue() / neg10Pow;
            }
        }
        value = val;

}
ExpressionElement::ExpressionElement(QChar a,QObject *parent) : QObject(parent)
{
    QRegExp regex("[0-9]");
    if (regex.exactMatch((QString)a))
    {
        type = number;
        value = a.digitValue();
    }
    else
    {
        type = operation;
        switch(a.combiningClass())
        {
            case '+':
                op = add;
                break;
            case '-':
                op = sub;
                break;
            case '*':
                op = multi;
                break;
            case '/':
                op = div;
                break;
            case '^':
                op = powa;
                break;
            default:
                op = none;
                emit error();
                break;


        }
    }
}
ExpressionElement::ExpressionElement( double whut,QObject *parent) : QObject(parent)
{
    type = number;
    value = whut;
}

QString ExpressionElement::toString()
{
    QString s;
    if (type == number)
    {
        s = QString::number(value);
    }
    else
    {
        s = QString::number(op);
    }
    return s;
}

double ExpressionElement::calc(ExpressionElement before, ExpressionElement after)
{
    double tempVal;
    switch(op)
    {
            case add:
                tempVal = before.value + after.value;
                break;
            case sub:
                tempVal = before.value - after.value;
                break;
            case multi:
                tempVal = before.value * after.value;
                break;
            case div:
                tempVal = before.value / after.value;
                break;
            case powa:
                tempVal = pow(before.value, after.value);
                break;
            default:
                emit error();
    }
    return tempVal;
}
