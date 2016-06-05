#include <algorithm>

#include "stringcalculator.h"


QVector<QString> StringCalculator::OP_ORDER; // Order of operations

StringCalculator::StringCalculator() {} // No constructor, this is a faux static class

// ========================================================================================================================================
// # Methods                                                                                                                              #
// ========================================================================================================================================

// setup()
//      Sets up the calculator for use, giving initalisation values such as
//      the order of operations and the operation mappings.
void StringCalculator::setup()
{
    // Setup the operation map for all the expression elements.
    ExpressionElement::setupOperationMap();

    // Put most imminent first.
    OP_ORDER.append("C");
    OP_ORDER.append("P");
    OP_ORDER.append("!");
    OP_ORDER.append("tan");
    OP_ORDER.append("cos");
    OP_ORDER.append("sin");
    OP_ORDER.append("^");
    OP_ORDER.append("pi");
    OP_ORDER.append("e");
    OP_ORDER.append("*");
    OP_ORDER.append("/");
    OP_ORDER.append("-");
    OP_ORDER.append("+");
}

// useDegrees(bool y)
//      Allows the user to set whether or not we should use degrees.
//      Only really modifies a static variable inside the ExpressionElement class
void StringCalculator::useDegrees(bool y)
{
    ExpressionElement::useDegrees(y);
}

// calculateQStringInput(QString input)
//
//
// Returns:
//      A double which is the mathematical equivalent of the input.
double StringCalculator::calculateQStringInput(QString input)
{
    QVector<ExpressionElement> expressionVector = genExpressionElements(input);
    ExpressionElement condensedElement = calculateVectorInput(expressionVector);
    double value = condensedElement.value_;
    return value;
}

// ---------------------------------------------------------------------------------------------------------------------------------------
// | Functions that are called by the calculator                                                                                         |
// ---------------------------------------------------------------------------------------------------------------------------------------

// genExpressionElements(QString input)
//      The parsing section of the calculator.
//
//      Generates an QVector of expression elements from a QString input
//      This QVector can then be processed to give a quantitative value.
QVector<ExpressionElement> StringCalculator::genExpressionElements(QString input)
{
    // Declare our output vector, starting with size 0.
    QVector<ExpressionElement> expressionVector = QVector<ExpressionElement>(0);

    // Index that determines where to start when searching for the next operation
    int crawlIndex = 0;

    while(crawlIndex < input.length())
    {
        //--------------------------------------------------------------------------------------------------------------------------------
        // Operation handling
        //--------------------------------------------------------------------------------------------------------------------------------

        // Check for operations
        if(input.at(crawlIndex) == QChar('['))
        {
            int operationEnd = input.indexOf("]", crawlIndex);

            // Is there a closing bracket?
            if(operationEnd < 0)
            {
                // INTERNAL ERROR
                // No closing bracket for operation
                throw 103;
            }
            else
            {
                // Add a new expression element to the vector
                expressionVector.append(ExpressionElement(input.mid(crawlIndex, operationEnd + 1 - crawlIndex)));
                crawlIndex = operationEnd + 1;
                continue;
            }
        }

        //--------------------------------------------------------------------------------------------------------------------------------
        // Subexpression handling
        //--------------------------------------------------------------------------------------------------------------------------------

        if(input.at(crawlIndex) == QChar('('))
        {

            // Turns out the below statement doesn't work.
            //int subexpressionEnd = input.indexOf(")", crawlIndex);
            int subexpressionEnd = crawlIndex+1; // A placeholder value for where the subexpression ends.
            int subexpressionCounter = 1; // Counts how many subexpressions we need to end.

            // Loop through the input, counting up all the open and close parens to find our matching one
            int parenI = subexpressionEnd;
            for(; parenI < input.size(); parenI++)
            {
                if(input.at(parenI) == QChar('('))
                {
                    subexpressionCounter++;
                }
                else if(input.at(parenI) == QChar(')'))
                {
                    subexpressionCounter--;
                    if(subexpressionCounter == 0)
                    {
                        // Stop incrementing parenI here.
                        break;
                    }
                }

                // We haven't found the close paren yet, increment parenI.
            }

            // We either found the closing paren or we didn't.
            // Assign it the value of the loop iterator.
            subexpressionEnd = parenI;

            if(subexpressionEnd < 0)
            {
                subexpressionEnd = input.size();
            }
            double subexpressionNet = calculateQStringInput(input.mid(crawlIndex + 1, subexpressionEnd - 1 - crawlIndex));

            // Support stuff like 5(10) = 50
            if(!expressionVector.isEmpty())
            {
                if(expressionVector.at(expressionVector.size()-1).isNumber_)
                {
                    expressionVector.append(ExpressionElement("[*]"));
                }
            }
            expressionVector.append(ExpressionElement(subexpressionNet));
            crawlIndex = subexpressionEnd + 1;
            continue;
        }




        //--------------------------------------------------------------------------------------------------------------------------------
        // Number handling
        //--------------------------------------------------------------------------------------------------------------------------------

        // Not an operation, so it must be a number.

        // Check to see if last element is a number so that we can multiply it to this one
        if(!expressionVector.isEmpty()) // Insure that the vector isn't empty yet.
        {
            if(expressionVector.at(expressionVector.size()-1).isNumber_)
            {
                expressionVector.append(ExpressionElement("[*]")); // Support stuff like (10)5 = 50
            }
        }

        int nextOperation = input.indexOf('[', crawlIndex);
        int nextSubexpression = input.indexOf("(", crawlIndex);

        if(nextOperation < 0)
        {
            nextOperation = input.size()+1;
        }

        if(nextSubexpression < 0)
        {
            nextSubexpression = input.size()+1;
        }

        // Get where the number should end, which is right up to next paren or bracket.
        int numberEnd = std::min(nextOperation, nextSubexpression);

        // Check to make sure we didn't somehow grab a close paren
        int closingBracketCheck = input.indexOf(')', crawlIndex);
        if(closingBracketCheck < numberEnd && closingBracketCheck >= 0)
        {
            // SYNTAX ERROR
            // Closing paren with no open paren.
            throw 104;
        }

        // Is there another operation?
        if(nextOperation < 0 && nextSubexpression < 0)
        {
            // No more operations or subexpressions. Append the last number.
            expressionVector.append(ExpressionElement(input.right(input.size() - crawlIndex)));
            break;
        }
        else
        {
            // More operations to go through!
            expressionVector.append(ExpressionElement(input.mid(crawlIndex, numberEnd - crawlIndex)));
            crawlIndex = numberEnd;
            continue;
        }

        crawlIndex++; // Just in case of infinite looping. Consider removing later.
    }

    return expressionVector; // return the expression vector output.
}

// calculateVectorInput(QVector<ExpressionElement> input)
//
//
//
ExpressionElement StringCalculator::calculateVectorInput(QVector<ExpressionElement> input)
{
    // Copy the old list that we will boil down to
    // a single expression element.
    QVector<ExpressionElement> modifiableVector = QVector<ExpressionElement>(input);

    // Put in implied constants at the beginning
    if(!input.at(0).isNumber_)
    {
        if(input.at(0).op_ == "-" || input.at(0).op_ == "+") // Allow for negative numbers
        {
            modifiableVector.insert(0, ExpressionElement(0));
        }
        else if(input.at(0).op_ == "*" || input.at(0).op_ == "/" || input.at(0).op_ == "^") // Complain when we begin with these
        {
            // SYNTAX ERROR
            throw 101;
        }
        else // Allow for stuff like "sin(45)" and "log(100)"
        {
            modifiableVector.insert(0, ExpressionElement(1));
        }
    }

    // Put in implied constants at the end.
    if(!input.at(input.size()-1).isNumber_)
    {
        if(input.at(input.size()-1).op_ == "pi"
                || input.at(input.size()-1).op_ == "e"
                || input.at(input.size()-1).op_ == "!")
        {
            modifiableVector.append(ExpressionElement(1));
        }
        else
        {
            // SYNTAX ERROR
            throw 102;
        }
    }

    if(modifiableVector.size() == 2)
    {
        // INTERNAL ERROR: It's impossible to have an ExpressionElement vector
        // of size 2
        throw 100;
    }

    //========================================================================================================================================
    // BEGIN LOOPS
    //========================================================================================================================================

    // Loop through every operation, in the order defined by OP_ORDER
    for(int opIndex = 0; opIndex < OP_ORDER.size(); opIndex++)
    {

        int opCount = 0; // Represents the number of this type of operation in the list.

        for(int e = 0; e < modifiableVector.size(); e++)
        {
            ExpressionElement elem = modifiableVector[e];
            if(!elem.isNumber_)
            {
                if(elem.op_ == OP_ORDER[opIndex]) // Check to see if this is our operation
                {
                    opCount++;
                }
            }
        }

        // Go through every operation of this type first and calculate it out.
        while(opCount > 0)
        {
            int i = 0; // Iterator for each operation
            while(i < modifiableVector.size()-2)
            {
                // Get the element in front of this one, and check if it's an operation.
                ExpressionElement opElement = modifiableVector[i+1];
                if(!opElement.isNumber_)
                {

                    if(opElement.op_ == OP_ORDER[opIndex])
                    {
                        // TODO:
                        // We need a try catch here for when the calc doesn't work
                        QVector<ExpressionElement> calculatedElements = opElement.calc(modifiableVector[i], modifiableVector[i+2]);

                        // Remove these 3 and substitute my own elements.
                        modifiableVector.removeAt(i+2);
                        modifiableVector.removeAt(i+1);
                        modifiableVector.removeAt(i);

                        for(int j = calculatedElements.size() - 1; j >= 0; j--)
                        {
                            // Insert the elements in reverse order. This is due to how insertion works.
                            modifiableVector.insert(i, calculatedElements.at(j));
                        }
                    }
                    opCount--; // We removed the element from the list
                }
                i++;
            }
        }
    }

    return modifiableVector[0];
}
