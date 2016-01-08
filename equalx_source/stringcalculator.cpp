#include <iostream>
#include <QApplication>
#include <QDebug>

#include "stringcalculator.h"

// Put header later
static QVector<Operation::Enum> OP_ORDER = QVector<Operation::Enum>();

int StringCalculator::subMain()
{
    OP_ORDER.append(Operation::powa);
    OP_ORDER.append(Operation::mult);
    OP_ORDER.append(Operation::div);
    OP_ORDER.append(Operation::add);
    OP_ORDER.append(Operation::sub);

    QVector<char> val1(0);
    val1.append('2');
    char vala = '^';
    QVector<char> val2(0);
    val2.append('1');
    val2.append('0');
    ExpressionElement o = ExpressionElement(val1);
    ExpressionElement a = ExpressionElement(vala);
    ExpressionElement t = ExpressionElement(val2);
    qDebug() << "Operation = " << a.calc(o, t) << '\n';



    return 0;
}

double StringCalculator::calculateCharVector(QVector<char> v)
{
    double value = 0;

    QVector<ExpressionElement> expressionList =  generateList(v);

    return 0.0;
}

QVector<ExpressionElement> StringCalculator::generateList(QVector<char> v)
{
    QVector<ExpressionElement> newList = QVector<ExpressionElement>();

    bool grabbingSubExpression = false;
    int subExpressionStartingIndex = -1;

    bool grabbingNumber = false;
    int numberStartingIndex = -1; // Index of start of each number.
    int numberEndingIndex = -1; // Index where the last number ended off on.

    for(unsigned int i = 0; i < v.size(); i++)
    {
        // Check for sub expressions first.
        if(v[i] == '(')
        {
            grabbingSubExpression = true;
            subExpressionStartingIndex = i+1;
            continue;
        }
        else if(v[i] == ')')
        {
            if(grabbingSubExpression)
            {
                grabbingSubExpression = false;
                char subExpression;
            }
        }
    }
}
