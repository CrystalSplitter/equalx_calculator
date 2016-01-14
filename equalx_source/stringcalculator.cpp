#include <iostream>
#include <QApplication>
#include <QDebug>

#include "stringcalculator.h"

// Put in header later
static QVector<Operation::Enum> OP_ORDER = QVector<Operation::Enum>();

// ============================================================================
// STRING CALCULATOR CODE
// ============================================================================

int StringCalculator::subMain()
{
    OP_ORDER.append(Operation::powa);
    OP_ORDER.append(Operation::mult);
    OP_ORDER.append(Operation::div);
    OP_ORDER.append(Operation::add);
    OP_ORDER.append(Operation::sub);

    QVector<char> val1 = convertToVector(QString("(9+3)^3"));
    double t = calculateCharVector(val1);

    qDebug() << t << '\n';
    return 0;
}

/*
 * calculateCharVector:
 *
 * First converts a char QVector to a ExpressionElement QVector
 * using generateVector. Then uses calculateList to get a single
 * ExpressionElement that represents the value inputted.
 *
 * Finally, returns the resulting double.
 */
double StringCalculator::calculateCharVector(QVector<char> v)
{
    QVector<ExpressionElement> expressionList = generateVector(v);
    ExpressionElement result = calculateList(expressionList);
    return result.value;
}

/*
 * calculateList:
 *
 * Calculates out a ExpressionElement QVector, and returns a *single* ExpressionElement
 * Which turns out, is pretty damn handy.
 *
 * This is done by iterating through OP_ORDER, which is organised in the order of PEMDAS.
 * First it finds the number of times the highest priority operation occurs, then it goes
 * and runs through, merging the ExpressionElements that surround that operation.
 *
 * This repeats until there is only a single ExpressionElement left, which in theory should
 * ALWAYS be a number type ExpressionElement.
 */
ExpressionElement StringCalculator::calculateList(QVector<ExpressionElement> elements)
{
    // Copy the old list that we will boil down to
    // a single expression element.
    QVector<ExpressionElement> newVector = QVector<ExpressionElement>(elements);

    // If the first element is an operation, put a 0 before it.
    // This allows us to properly handle things like negative numbers.
    if(!elements[0].isNumber)
        newVector.append(ExpressionElement(0.0));

    if(newVector.size() == 2)
    {
        // TODO:
        //SYNTAX ERROR
    }

    // Loop through every operation, in the order defined by OP_ORDER
    for(int opIndex = 0; opIndex < OP_ORDER.size(); opIndex++)
    {
        int opCount = 0; // Represents the number of this type of operation in the list.

        for(int e = 0; e < newVector.size(); e++)
        {
            ExpressionElement elem = newVector[e];
            if(!elem.isNumber)
            {
                if(elem.op == OP_ORDER[opIndex]) { // Check to see if this is our operation
                    opCount++;
                }
            }
        }

        while(opCount > 0)
        {

            int i = 0; // Iterator for each operation
            while(i < newVector.size()-2)
            {
                // Get the element in front of this one, and check
                // if it's an operation.
                ExpressionElement elem = newVector[i+1];
                if(!elem.isNumber)
                {
                    if(elem.op == OP_ORDER[opIndex])
                    {
                        // TODO:
                        // We need a try catch here for when the calc doesn't work
                        double eval = elem.calc(newVector[i], newVector[i+2]);
                        newVector[i] = ExpressionElement(eval);
                        newVector.removeAt(i+2);
                        newVector.removeAt(i+1);
                    }
                    opCount--;
                }
                i++;
            }
        }
    }

    return newVector[0];
}

/*
 * generateVector:
 *
 * Generates a QVector of ExpressionElements by parsing a QVector of characters
 * This is vital, as to calculate the inputted string, the iterable (in this case
 * the QVector) must be homogenous. Meaning, it has to be made up of all the same
 * types of classes. In this case, ExpressionElement fills this role.
 *
 * Please note, when encountering subexpressions (things surrounded by
 * parentheses), the generation recursively calls calculateCharVector,
 * which in turn will generate a new ExpressionElement QVector for us.
 */
QVector<ExpressionElement> StringCalculator::generateVector(QVector<char> inputVector)
{
    QVector<ExpressionElement> newVector = QVector<ExpressionElement>(0);

    bool grabbingSubExpression = false;
    int subExpressionStartingIndex = -1;

    bool grabbingNumber = false;
    int numberStartingIndex = -1; // Index of start of each number.
    int numberEndingIndex = -1; // Index where the last number ended off on.


    for(int i = 0; i < inputVector.size(); i++)
    {
        // --------------------------------------------------------------------
        // SUB EXPRESSION HANDLING
        // --------------------------------------------------------------------

        // Check for sub expressions first.
        if(inputVector[i] == '(')
        {
            grabbingSubExpression = true;
            subExpressionStartingIndex = i+1; // Starts at the next character
            continue; // Move to next character
        }
        else if(inputVector[i] == ')')
        {
            if(grabbingSubExpression)
            {
                grabbingSubExpression = false; // Close the sub expression off

                // Recursively create the sub expression elements
                QVector<char> subExpression = QVector<char>();
                // q is an iterator!
                for(int q = subExpressionStartingIndex; q < i; q++)
                {
                    subExpression.append(inputVector[q]);
                }
                double subValue = calculateCharVector(subExpression);
                newVector.append(ExpressionElement(subValue));
                continue; // Move to next character
            }
            else
            {
                // TODO:
                // SYNTAX ERROR: Closing paren but no opening paren
            }
        }

        if(grabbingSubExpression)
            continue;

        // --------------------------------------------------------------------
        // NUMBER HANDLING
        // --------------------------------------------------------------------

        // Now check for actual numbers.
        bool isNumber = isdigit(inputVector[i]);
        bool isPoint = (inputVector[i] == '.');

        // Check to see if we are
        if(i == inputVector.size()-1 && (!isNumber && !isPoint))
        {
            // TODO:
            // SYNTAX ERROR: ENDED IN OPERATION
            break;
        }

        if(i != inputVector.size() - 1 && (isNumber || isPoint))
        {
            // Did we just started grabbing a number?
            if(!grabbingNumber)
            {
                numberStartingIndex = i;
                grabbingNumber = true;
            }
            continue;
        }
        else if(grabbingNumber)
        {
            // We were grabbing a number but now we aren't.
            grabbingNumber = false;

            // Did we get here because we reached the EOL or
            // because we hit a non-number?
            if(i == inputVector.size()-1)
            {
                numberEndingIndex = i+1; // Move the ending index to the EOL
            }
            else
            {
                numberEndingIndex = i; // Move the ending index to this character
            }

            // Begin subVector generation -------------------------------------
            QVector<char> subCharVector = QVector<char>();
            // q is an iterator!
            for(int q = numberStartingIndex; q < numberEndingIndex; q++)
            {
                subCharVector.append(inputVector[q]);
            }
            // End subVector generation ---------------------------------------

            newVector.append(ExpressionElement(subCharVector));
        }
        newVector.append(ExpressionElement(inputVector[i]));
    }
    return newVector;
}

// ============================================================================
// UTILITIES
// ============================================================================

/*
 * convertToVector:
 *
 * Converts a QString to a char QVector.
 */
QVector<char> StringCalculator::convertToVector(QString s)
{
    QVector<char> newVector = QVector<char>(s.length());
    for(int i = 0; i < s.length(); i++)
    {
        newVector[i] = s.at(i).toLatin1();
    }
    return newVector;
}
