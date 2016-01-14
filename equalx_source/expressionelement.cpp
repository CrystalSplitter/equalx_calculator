#include <string>
#include <QApplication>
#include <QDebug>
#include <math.h>

#include "expressionelement.h"


ExpressionElement::ExpressionElement() : ExpressionElement::ExpressionElement(0.0) {}

ExpressionElement::ExpressionElement(double val)
{
    this->isNumber = true;
    this->op = Operation::none;
    this->value = val;
}

ExpressionElement::ExpressionElement(char c)
{
    initA(c);
}

ExpressionElement::ExpressionElement(QVector<char> v)
{
    // Assuming we did the numbe collection correctly,
    // this is a number type ExpressionElement
    this->isNumber = true;

    if(v.size() == 1)
    {
        initA(v[0]);
        return;
    }

    // Running value
    double val = 0;

    // While it shouldn't be signed,
    // negative values can be helpful for error checking
    int decimalPosition = -1;

    // Loop through each element in the char array
    for(int i = 0; i < v.size(); i++)
    {
        // Check for decimal points
        if(v[i] == '.')
        {
            if(decimalPosition >= 0)
            {
                // 2 DECIMAL POINTS ERROR
                continue;
            }
            else
            {
                decimalPosition = i;
                continue;
            }
        }

        if(decimalPosition < 0)
        {
            // Remember to shift by 48
            val = val * 10 + ((int) v[i]) - 48;
        }
        else
        {
            double neg10Pow = (double) (10*(1-decimalPosition));
            val = val + (((int) v[i]) - 48)/neg10Pow;
        }
        this->value = val;
    }
}

void ExpressionElement::initA(char c)
{
    const bool numberCheck = isdigit(c);

    if(numberCheck)
    {
        this->isNumber = true;
        this->op = Operation::none;
        // Convert the digit to ascii, then shift it by 48.
        this->value = ((int) c) - 48;
    }
    else
    {
        this->isNumber = false;
        switch(c)
        {
            case '+':
                this->op = Operation::add;
                break;
            case '-':
                this->op = Operation::sub;
                break;
            case '*':
                this->op = Operation::mult;
                break;
            case '/':
                this->op = Operation::div;
                break;
            case '^':
                this->op = Operation::powa;
                break;
            default:
                this->op = Operation::none;
                // ERROR: Not a number nor a valid operator
                throw 200;
                break;
        }
    }
}

QString ExpressionElement::toString()
{
    // Returning string
    QString s;

    if(this->isNumber == true)
    {
        s = QString::number(this->value);
    }
    else
    {
        s = static_cast<char>(this->op);
    }
    return s;
}

double ExpressionElement::calc(ExpressionElement before, ExpressionElement after)
{
    if((this->isNumber) || !(before.isNumber) || !(after.isNumber))
    {
        // SYNTAX ERROR: The expression is either
        //    - not an operator
        //    - not surrounded by number elements (such as "+*+")
        throw 201;

    }

    double value;

    switch(this->op)
    {
        case Operation::add:
            value = before.value + after.value;
            break;
        case Operation::sub:
            value = before.value - after.value;
            break;
        case Operation::mult:
            value = before.value * after.value;
            break;
        case Operation::div:
            value = before.value / after.value;
            break;
        case Operation::powa:
            value = pow(before.value, after.value);
            break;
        case Operation::none:
            value = 0;
            // ERROR: Not a number nor a valid operator
            throw 202;
            break;
    }

    return value;
}
