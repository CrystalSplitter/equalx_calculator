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

// Single character initiator
// May be removed eventually
ExpressionElement::ExpressionElement(char c)
{
    initA(c);
}

ExpressionElement::ExpressionElement(QVector<char> v)
{

    // Before we check for numbers, make sure we aren't in a special operation.
    for(int i = 0; i < POSSIBLE_OPS.size(); i++)
    {
        QVector<char> op_vector = Utilities::convertToVector(POSSIBLE_OPS[i]);
        if(Utilities::vectorComparison(op_vector, v))
        {
            this->isNumber = false;
            setOperation(POSSIBLE_OPS[i]);
            return;
        }
    }

    // Assuming we did the number collection correctly,
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
    const bool numberCheck = isdigit;

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
        if(!setOperation(QString(c)))
        {
            throw 200;
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

/*
 * setOperation
 *
 * Sets the operation based on an inputted QString
 */
bool ExpressionElement::setOperation (QString s)
{
    /*
    switch(s)
    {
        case QString("+"):
            this->op = Operation::add;
            return true;
        case QString("-"):
            this->op = Operation::sub;
            return true;
        case QString("*"):
            this->op = Operation::mult;
            return true;
        case QString("/"):
            this->op = Operation::div;
            return true;
        case QString("^"):
            this->op = Operation::powa;
            return true;
        case QString("log"):
            this->op = Operation::log;
            return true;
        case QString("ln"):
            this->op = Operation::ln;
            return true;
        default:
            this->op = Operation::none;
            // ERROR: Not a number nor a valid operator
            return false;
            break;
    }
    */
    return false;
}
