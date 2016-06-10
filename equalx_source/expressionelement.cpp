#include "expressionelement.h"

// Define the static private variables
std::map<QString,int> ExpressionElement::opToIntMap_;
bool ExpressionElement::useDeg_ = true;
double ExpressionElement::conversion_ = M_PI/180;

// Default constructor
ExpressionElement::ExpressionElement() : ExpressionElement::ExpressionElement(0.0) {}

// Constructor for Double arguement
//      Takes a double in, and sets to a number.
//      Sets the value to the argument provided.
ExpressionElement::ExpressionElement(double val)
{
    this->isNumber_ = true;
    this->op_ = QString("None");
    this->value_ = val;
}

// Constructor for a QString
//      Forms an expression element from a QString, this is done by
//      checking first to see if it's a function. If not, the constructor
//      will treat it as if it was a double.
ExpressionElement::ExpressionElement(QString s)
{
    if(s.at(0) == QChar('[') && s.at(s.length()-1) == QChar(']'))
    {
        this->isNumber_ = false;
        this->op_ = s.mid(1, s.length()-2);
    }
    else
    {
        this->isNumber_ = true;
        this->op_ = QString("None");
        this->value_ = s.toDouble();
    }
}

// Converts this expression element to a QString
QString ExpressionElement::toString() const
{
    // Returning string
    QString s;

    if(this->isNumber_ == true)
    {
        s = QString::number(this->value_);
    }
    else
    {
        s = this->op_;
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
    ExpressionElement::opToIntMap_[QString("+")] = 0x000000002B;
    ExpressionElement::opToIntMap_[QString("-")] = 0x000000002D;
    ExpressionElement::opToIntMap_[QString("*")] = 0x000000002A;
    ExpressionElement::opToIntMap_[QString("/")] = 0x000000002F;
    ExpressionElement::opToIntMap_[QString("^")] = 0x000000005E;
    ExpressionElement::opToIntMap_[QString("log")] =  0x00006C6F67;
    ExpressionElement::opToIntMap_[QString("ln")] =  0x0000006C6E;
    ExpressionElement::opToIntMap_[QString("sin")] = 0x000073696E;
    ExpressionElement::opToIntMap_[QString("cos")] = 0x0000636F73;
    ExpressionElement::opToIntMap_[QString("tan")] = 0x000074616E;
    ExpressionElement::opToIntMap_[QString("sinh")] = 0x0073696E68;
    ExpressionElement::opToIntMap_[QString("cosh")] = 0x00636F7368;
    ExpressionElement::opToIntMap_[QString("tanh")] = 0x0074616E68;
    ExpressionElement::opToIntMap_[QString("asin")] = 0x006173696E;
    ExpressionElement::opToIntMap_[QString("acos")] = 0x0061636F73;
    ExpressionElement::opToIntMap_[QString("atan")] = 0x006174616E;
    ExpressionElement::opToIntMap_[QString("!")] = 0x0000000021;
    ExpressionElement::opToIntMap_[QString("P")] = 0x0000000050;
    ExpressionElement::opToIntMap_[QString("C")] = 0x0000000043;
    ExpressionElement::opToIntMap_[QString("pi")] = 0x0000007069;
    ExpressionElement::opToIntMap_[QString("e")] = 0x0000000065;
    // TODO: Make more operations!
}

// Combines 3 expression elements together and returns a number expression element.
//      This only works if they are in a valid order for the specific operation.
//      Each operation has its own requirements.
//      Elsewise there will be errors.
QVector<ExpressionElement> ExpressionElement::calc(ExpressionElement before, ExpressionElement after)
{
    bool validSimpleOp = true;

    // For special functions, such as trig and factorial, we don't really want to return a value.
    // Rather, we want to calculate
    QVector<ExpressionElement> outputVector = QVector<ExpressionElement>(0);

    bool returnBefore = false;
    bool returnAfter = false;

    if((this->isNumber_))
    {
        // SYNTAX ERROR: The expression is not an operator
        throw 201;
    }

    // Simple operations are + - * / ^ and a few others
    if(!before.isNumber_ || !after.isNumber_)
    {
        //not surrounded by number elements (such as "+*+")
        validSimpleOp = false;
    }

    double value = 0;

    // Go through each viable operation that we've made so far.
    // If we want to make more operations, add them here!
    switch(ExpressionElement::opToIntMap_[this->op_])
    {
        case 0x000000002B:
            // Addition
            if(validSimpleOp)
            {
                value = before.value_ + after.value_;
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
                value = before.value_ - after.value_;
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
                value = before.value_ * after.value_;
            }
            else
            {
                throw 203;
            }
            break;
        case 0x000000002F:
            {
                // Division
                if(validSimpleOp && after.value_)
                {
                    if(after.value_ == 0)
                    {
                        // Since C++ supports
                        // division by zero with floats,
                        // we should add a special case where
                        //
                        throw 204;
                    }
                    value = before.value_ / after.value_;
                }
                else
                {
                   throw 203;
                }
                break;
            }
        case 0x0000000065:
            // the natural number e
            value = M_E;

            if(before.isNumber_)
            {
                value *= before.value_;
            }
            else
            {
                returnBefore = true;
            }

            if(after.isNumber_)
            {
                value *= after.value_;
            }
            else
            {
                returnAfter = true;
            }
            break;
        case 0x000000005E:
            {
                // Exponent
                if(validSimpleOp)
                {
                    value = pow(before.value_, after.value_);
                }
                else
                {
                   throw 203;
                }
                break;
            }
        case 0x00006C6F67:
            {
                // Logarithm
                double coefficient = 1.0;
                if(!after.isNumber_)
                {
                    throw 203;
                }
                else if(after.value_ <= 0)
                {
                    throw 204;
                }
                else if(!before.isNumber_)
                {
                    returnBefore = true;
                }
                else
                {
                    coefficient = before.value_;
                }
                value = coefficient * log10(after.value_);
                break;
            }
        case 0x0000006C6E:
            {
                // Natural Logarithm
                double coefficient = 1.0;
                if(!after.isNumber_)
                {
                    throw 203;
                }
                else if(after.value_ <= 0)
                {
                    throw 204;
                }
                else if(!before.isNumber_)
                {
                    returnBefore = true;
                }
                else
                {
                    coefficient = before.value_;
                }
                value = coefficient * log(after.value_);
                break;
            }
        case 0x0000007069:
            // Pi
            value = M_PI;

            if(before.isNumber_)
            {
                value *= before.value_;
            }
            else
            {
                returnBefore = true;
            }

            if(after.isNumber_)
            {
                value *= after.value_;
            }
            else
            {
                returnAfter = true;
            }
            break;
        case 0x000073696E:
            {
                // Sine
                if(!after.isNumber_)
                {
                    throw 203;
                }

                if(before.isNumber_)
                {
                    value = before.value_ * sin(after.value_*conversion_);
                }
                else
                {
                    value = sin(after.value_*conversion_);
                    returnBefore = true;
                }
                break;
            }
        case 0x0000636F73:
            {
                // Cosine
                if(!after.isNumber_)
                {
                    throw 203;
                }

                if(before.isNumber_)
                {
                    value = before.value_ * cos(after.value_*conversion_);
                }
                else
                {
                    value = cos(after.value_ * conversion_);
                    returnBefore = true;
                }
                break;
            }
        case 0x000074616E:
            {
                // Tangent
                if(!after.isNumber_)
                {
                   throw 203;
                }

                if(before.isNumber_)
                {
                    value = before.value_ * tan(after.value_ * conversion_);
                }
                else
                {
                    value = tan(after.value_ * conversion_);
                    returnBefore = true;
                }
                break;
            }
        case 0x0073696E68:
            // Hyperbolic Sine
            if(!after.isNumber_)
            {
               throw 203;
            }

            if(before.isNumber_)
            {
                value = before.value_ * sinh(after.value_ * conversion_);
            }
            else
            {
                value = sinh(after.value_ * conversion_);
                returnBefore = true;
            }
            break;
        case 0x00636F7368:
            // Hyperbolic Cosine
            if(!after.isNumber_)
            {
               throw 203;
            }

            if(before.isNumber_)
            {
                value = before.value_ * cosh(after.value_ * conversion_);
            }
            else
            {
                value = cosh(after.value_ * conversion_);
                returnBefore = true;
            }
            break;
        case 0x0074616E68:
            // Hyperbolic Tangent
            if(!after.isNumber_)
            {
               throw 203;
            }

            if(before.isNumber_)
            {
                value = before.value_ * tanh(after.value_ * conversion_);
            }
            else
            {
                value = tanh(after.value_ * conversion_);
                returnBefore = true;
            }
            break;
        case 0x006173696E:
            {
                // Arcsine
                if(!after.isNumber_)
                {
                   throw 203;
                }

                if(before.isNumber_)
                {
                    value = before.value_ *  asin(after.value_) / conversion_;
                }
                else
                {
                    value = asin(after.value_) / conversion_;
                    returnBefore = true;
                }
                break;
            }
        case 0x0061636F73:
            {
                // Arccosine
                if(!after.isNumber_)
                {
                   throw 203;
                }

                if(before.isNumber_)
                {
                    value = before.value_ * acos(after.value_) / conversion_;
                }
                else
                {
                    value = acos(after.value_) / conversion_;
                    returnBefore = true;
                }
                break;
            }
        case 0x006174616E:
            {
                // Arctangent
                if(!after.isNumber_)
                {
                   throw 203;
                }

                if(before.isNumber_)
                {
                    value = before.value_ *  atan(after.value_) / conversion_;
                }
                else
                {
                    value = atan(after.value_) / conversion_;
                    returnBefore = true;
                }
                break;
            }
        case 0x0000000021:
            {
                // Factorial
                double multVal = 1; // Multiply this at the end

                if(after.isNumber_)
                {
                    // If there's a number after
                    // the factorial, multiply it to the end
                    multVal = after.value_;
                }
                else
                {
                    // If there's an operation instead,
                    // return it with the output.
                    returnAfter = true;
                }

                if(!before.isNumber_)
                {
                    throw 203;
                }
                else
                {
                    value = (double) ExpressionElement::factorial(before.value_);
                }

                // Multiply by the right number if it exists.
                value = value * multVal;
                break;
            }
        case 0x0000000050:
            // Permutations
            // Make sure that there are integers before and after
            // the P.
            if(!validSimpleOp)
            {
                throw 203;
            }

            value = (double) (ExpressionElement::factorial(before.value_) / ExpressionElement::factorial(before.value_-after.value_));
            break;
        case 0x0000000043:
            {
                // Combinations
                // Make sure that there are integers before and after
                // the C.
                if(!validSimpleOp)
                {
                    throw 203;
                }

                double denom = ExpressionElement::factorial(before.value_-after.value_)*ExpressionElement::factorial(after.value_);
                value = (double) (ExpressionElement::factorial(before.value_) / denom);
                break;
            }
        default:
            // INTERNAL ERROR: Not a number nor a valid operator
            throw 202;
            break;
    }

    if(abs(value) > pow(10, 100))
    {
        // INTERNAL ERROR
        // Answer is outside calculator bounds.
        throw 204;
    }

    // Return the expression element before this one?
    if(returnBefore)
    {
        outputVector.append(before);
    }

    // Append the actual number to output vector

    ExpressionElement numberElement = ExpressionElement(value);
    outputVector.append(numberElement);

    // Return the expression element after this one?
    if(returnAfter)
    {
        outputVector.append(after);
    }

    return outputVector;
}

void ExpressionElement::useDegrees(bool y)
{
    ExpressionElement::useDeg_ = y;
    if(y)
    {
        conversion_ = M_PI/180;
    }
    else
    {
        conversion_ = 1;
    }
}

// factorial()
//      Takes a double and makes sure that it is an integer
//      Returns the output which while is numerically always
//      an integer, returns it as a long because factorials
//      tend to get very large quickly.
double ExpressionElement::factorial(double x)
{
    // Get integer value of the left number.
    // We do not use the gamma function.
    int integerInput = (int) x;

    if((x - integerInput > 0)
        || (x < 0))
    {
        // Can't do factorial of non-integers and
        // negative numbers.
        throw 203;
    }
    else if(integerInput == 0)
    {
        // By definition, 0! = 1
        return 1;
    }

    // Use a double here due to the ability to store the significand.
    // The significand is what will matter in the end eventually anyways.
    // Using longs will usually overflow, unfortunately.
    QVector<double> factorialSaveVector = QVector<double>(x);
    factorialSaveVector[0] = x;
    for(int i = 1; i < factorialSaveVector.size(); i++)
    {
        factorialSaveVector[i] = (double) factorialSaveVector.at(i-1) * (x-i);
    }
    return factorialSaveVector.last();
}
