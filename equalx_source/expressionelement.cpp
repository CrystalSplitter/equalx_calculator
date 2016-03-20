#include "expressionelement.h"

// Define the static private variables
std::map<QString,int> ExpressionElement::opToIntMap;
bool ExpressionElement::useDeg = true;

// Default constructor
ExpressionElement::ExpressionElement() : ExpressionElement::ExpressionElement(0.0) {}

// Constructor for Double arguement
//      Takes a double in, and sets to a number.
//      Sets the value to the argument provided.
ExpressionElement::ExpressionElement(double val)
{
    this->isNumber = true;
    this->op = QString("None");
    this->value = val;
}

// Constructor for a QString
//      Forms an expression element from a QString, this is done by
//      checking first to see if it's a function. If not, the constructor
//      will treat it as if it was a double.
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
        this->op = QString("None");
        this->value = s.toDouble();
    }
}

// Converts this expression element to a QString
QString ExpressionElement::toString() const
{
    // Returning string
    QString s;

    if(this->isNumber == true)
    {
        s = QString::number(this->value);
    }
    else
    {
        s = this->op;
    }
    return s;
}


// Setup the Operation map
//     This determines the integers that are assigned to
//      new functions.
void ExpressionElement::setupOperationMap()
{
    // Setup the dictionaris to convert QStrings to hex digits
    // this system allows functions to be 5 characters long:
    //      -Convert the function's ascii chars to hex.
    //      -Put them in the map.
    ExpressionElement::opToIntMap[QString("+")] = 0x000000002B;
    ExpressionElement::opToIntMap[QString("-")] = 0x000000002D;
    ExpressionElement::opToIntMap[QString("*")] = 0x000000002A;
    ExpressionElement::opToIntMap[QString("/")] = 0x000000002F;
    ExpressionElement::opToIntMap[QString("^")] = 0x000000005E;
    ExpressionElement::opToIntMap[QString("sin")] = 0x000073696E;
    // TODO: Make more operations!
}

// Combines 3 expression elements together and returns a number expression element.
//      This only works if they are in the correct order, which is:
//
//          Double Operation Double
//
//      Elsewise there will be errors.
QVector<ExpressionElement> ExpressionElement::calc(ExpressionElement before, ExpressionElement after)
{
    bool validSimpleOp = true;

    // For special functions, such as trig and factorial, we don't really want to return a value.
    // Rather, we want to calculate
    QVector<ExpressionElement> outputVector = QVector<ExpressionElement>(0);

    bool returnBefore = false;
    bool returnAfter = false;

    if((this->isNumber))
    {
        // SYNTAX ERROR: The expression is not an operator
        throw 201;
    }

    // Simple operations are + - * / ^ and a few others
    if(!before.isNumber || !after.isNumber)
    {
        //not surrounded by number elements (such as "+*+")
        validSimpleOp = false;
    }

    double value = 0;

    // Go through each viable operation that we've made so far.
    // If we want to make more operations, add them here!
    switch(ExpressionElement::opToIntMap[this->op])
    {
        case 0x000000002B:
            // Addition
            if(validSimpleOp)
            {
                value = before.value + after.value;
            }
            else
            {
                throw 203;
            }
            break;
        case 0x000000002D:
            // Subtraction
            if(validSimpleOp)
            {
                value = before.value - after.value;
            }
            else
            {
                throw 203;
            }
            break;
        case 0x000000002A:
            // Multiplication
            if(validSimpleOp)
            {
                value = before.value * after.value;
            }
            else
            {
                throw 203;
            }
            break;
        case 0x000000002F:
        {
            // Division
            if(validSimpleOp)
            {
                value = before.value / after.value;
            }
            else
            {
               throw 203;
            }
            break;
        }
        case 0x000000005E:
        {
            // Exponent
            if(validSimpleOp)
            {
                value = pow(before.value, after.value);
            }
            else
            {
               throw 203;
            }
            break;
        }
        case 0x000073696E:
        {
            // Sine
            if(!after.isNumber)
            {
                throw 203;
            }

            double conversion = 1;
            if(ExpressionElement::useDeg)
            {
                conversion = M_PI/180;
            }

            if(before.isNumber)
            {
                value = before.value * sin(after.value*conversion);
            }
            else
            {
                value = sin(after.value*conversion);
                returnBefore = true;
            }

            break;
        }
        default:
            // ERROR: Not a number nor a valid operator
            throw 202;
            break;
    }

    if(returnBefore)
    {
        outputVector.append(before);
    }

    // Append the actual number to output vector
    ExpressionElement numberElement = ExpressionElement(value);
    outputVector.append(numberElement);

    if(returnAfter)
    {
        outputVector.append(after);
    }

    return outputVector;
}

void ExpressionElement::useDegrees(bool y)
{
    ExpressionElement::useDeg = y;
}
