#ifndef UTILITIES_H
#define UTILITIES_H


class ExpressionElement;

#include "operation.h"
#include <QApplication>

class Utilities
{

public:
    static QVector<char> convertToVector(QString);
    static bool vectorComparison(QVector<char>, QVector<char>);
    static QString betterVectorPrint(QVector<char>);
    static QString betterVectorPrint(ExpressionElement*);
    static Operation::Enum convertVectorToOP(QVector<char>);
};

#endif // UTILITIES_H
