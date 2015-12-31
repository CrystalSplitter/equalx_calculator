#include "expressionelement.h"
#include <stdlib.h>
#include <regex>
#include <math.h>
#include <string>

ExpressionElement::ExpressionElement(char* a,QObject *parent) : QObject(parent)
{

        op = none;
        type = number;
        val = 0;
        bool belowDecimal = false;
        int decimalPosition = -1;
        value = 0;

        for (int i = 0; i < sizeof(a); i++)
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
                val = val * 10 + atoi(&a[i]);
            }
            else
            {
                double neg10Pow = (double)(10*(i-decimalPosition));
                val = val + atoi(&a[i]) / neg10Pow;
            }
        }
        value = val;

}
ExpressionElement::ExpressionElement(char a,QObject *parent) : QObject(parent)
{
    QRegExp regex("[0-9]");
    if (regex.exactMatch((QString)a))
    {
        type = number;
        value = atoi(&a);
    }
    else
    {
        type = operation;
        switch(a)
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

double ExpressionElement::calc(ExpressionElement* before, ExpressionElement* after)
{
    double tempVal;
    switch(op)
    {
            case add:
                tempVal = before->value + after->value;
                break;
            case sub:
                tempVal = before->value - after->value;
                break;
            case multi:
                tempVal = before->value * after->value;
                break;
            case div:
                tempVal = before->value / after->value;
                break;
            case powa:
                tempVal = pow(before->value, after->value);
                break;
            default:
                emit error();
    }
    return tempVal;
}
