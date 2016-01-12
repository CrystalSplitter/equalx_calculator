#ifndef EXPRESSIONELEMENT_H
#define EXPRESSIONELEMENT_H

#include <QObject>
#include <QRegExp>
#include <QVector>
class ExpressionElement : public QObject
{
    Q_OBJECT
public:
    explicit ExpressionElement(QVector<QChar>, QObject *parent = 0);
    explicit ExpressionElement(QChar,QObject *parent = 0);
    explicit ExpressionElement(double, QObject *parent = 0);
    enum Operation{none, add, sub, multi, div, powa}; // The types of operations available on this calculator
    enum ExpressionElemType{number,operation};
 /*
    * Enumeration to determine the ExpressionElement type.
    * Depending on the type, the expression is handled differently.
 */
    ExpressionElemType type;
    Operation op;
    double val, value;
signals:
    void error();
public slots:
    QString toString();
    double calc(ExpressionElement before, ExpressionElement after);
};

#endif // EXPRESSIONELEMENT_H
