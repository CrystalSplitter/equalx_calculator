#include <string>
#include <QApplication>
#include <QDebug>
#include <math.h>

#include "expressionelement.h"

static std::map<QVector<char>, Operation::Enum> OPERATION_MAP;
static QVector<QString> POSSIBLE_OPS = QVector<QString>();

// Default constructor
ExpressionElement::ExpressionElement() : ExpressionElement::ExpressionElement(0.0) {}

// Double constructor
ExpressionElement::ExpressionElement(double val)
{
    this->isNumber = true;
    this->op = Operation::none;
    this->value = val;
}

ExpressionElement::ExpressionElement(QString s)
{
    if(s.at(0) == QChar('[') && s.at(s.length()-1) == QChar(']'))
    {
        this->isNumber = false;
        this->op = s.mid(1, s.length()-2);
    }
    else
    {
        this->isNumber = true;
    }
}

QString ExpressionElement::toString()
{
    // Returning string
    QString s;

    if(this->isNumber == true)
    {
        s = this->value;
    }
    else
    {
        s = this->op;
    }
    return s;
}

ExpressionElement ExpressionElement::calc(ExpressionElement before, ExpressionElement after)
{
    /*
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
    */

    return before;
}
