#include <algorithm>

#include "stringcalculator.h"


QVector<QString> StringCalculator::OP_ORDER; // Order of operations

StringCalculator::StringCalculator() {} // No constructor, this is a faux static class

// =======================================================================
// # Methods                                                             #
// =======================================================================

// setup()
//      Sets up the calculator for use, giving initalisation values such as
//      the order of operations and the operation mappings.
void StringCalculator::setup()
{
    // Setup the operation map for all the expression elements.
    ExpressionElement::setupOperationMap();

    OP_ORDER.append("tan");
    OP_ORDER.append("sin");
    OP_ORDER.append("cos");
    OP_ORDER.append("^");
    OP_ORDER.append("*");
    OP_ORDER.append("/");
    OP_ORDER.append("+");
    OP_ORDER.append("-");
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
    double value = condensedElement.value;
    return value;
}

// -----------------------------------------------------------------------
// | Functions that are called by the calculator                         |
// -----------------------------------------------------------------------

// genExpressionElements(QString input)
//      The parsing section of the calculator.
//
//      Generates an QVector of expression elements from a QString input
//      This QVector can then be processed to give a quantitative value.
QVector<ExpressionElement> StringCalculator::genExpressionElements(QString input)
{
    // Declare our output vector, starting with size 0.
    QVector<ExpressionElement> expressionVector = QVector<ExpressionElement>(0);


    // Declare some variables for dealing with sub-expressions
    int subExpressionCount = 0;
    int subExpressionStartingIndex = -1;

    // Index that determines where to start when searching for the next operation
    int crawlIndex = 0;

    while(crawlIndex < input.length())
    {

        //----------------------------------------------------------------
        // Operation handling
        //----------------------------------------------------------------

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

        //----------------------------------------------------------------
        // Subexpression handling
        //----------------------------------------------------------------

        if(input.at(crawlIndex) == QChar('('))
        {
            int subexpressionEnd = input.indexOf(")", crawlIndex);

            if(subexpressionEnd < 0)
            {
                subexpressionEnd = input.size();
            }
            double subexpressionNet = calculateQStringInput(input.mid(crawlIndex + 1, subexpressionEnd - 1 - crawlIndex));

            // Support stuff like 5(10) = 50
            if(!expressionVector.isEmpty())
            {
                if(expressionVector.at(expressionVector.size()-1).isNumber)
                {
                    expressionVector.append(ExpressionElement("[*]"));
                }
            }
            expressionVector.append(ExpressionElement(subexpressionNet));
            crawlIndex = subexpressionEnd + 1;
            continue;
        }

        //----------------------------------------------------------------
        // Number handling
        //----------------------------------------------------------------

        // Not an operation, so it must be a number.

        // Check to see if last element is a number so that we can multiply it to this one
        if(!expressionVector.isEmpty()) // Insure that the vector isn't empty yet.
        {
            if(expressionVector.at(expressionVector.size()-1).isNumber)
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

    // TODO: Instead of addition of 0, use multiply by -1
    if(!input[0].isNumber)
    {
        if(input[0].op == "-")
        {
            modifiableVector.insert(0, ExpressionElement(0));
        }
        else
        {
            modifiableVector.insert(0, ExpressionElement(1));
        }
    }

    if(modifiableVector.size() == 2)
    {
        // INTERNAL ERROR: It's impossible to have an ExpressionElement vector
        // of size 2
        throw 100;
    }


    // Loop through every operation, in the order defined by OP_ORDER
    for(int opIndex = 0; opIndex < OP_ORDER.size(); opIndex++)
    {

        int opCount = 0; // Represents the number of this type of operation in the list.

        for(int e = 0; e < modifiableVector.size(); e++)
        {
            ExpressionElement elem = modifiableVector[e];
            if(!elem.isNumber)
            {
                if(elem.op == OP_ORDER[opIndex]) // Check to see if this is our operation
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
                if(!opElement.isNumber)
                {

                    if(opElement.op == OP_ORDER[opIndex])
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
