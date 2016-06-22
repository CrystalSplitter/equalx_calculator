#ifndef EXPRESSIONELEMENT_H
#define EXPRESSIONELEMENT_H

#include "QApplication"
#include <QDebug>
#include <math.h>

class ExpressionElement
{
    public:
        bool isNumber_ = true;
        QString op_ = "None";
        double value_ = 0;
    private:
        static std::map<QString,int> opToIntMap_;
        static bool useDeg_;
        static double conversion_;

    public:
        ExpressionElement();
        ExpressionElement(QString);
        ExpressionElement(double);
        QString toString() const;
        QVector<ExpressionElement> calc(ExpressionElement, ExpressionElement);
        static void setupOperationMap();
        static void useDegrees(bool);
    private:
        bool setOperation(QString);
        static double factorial(double);

};

#endif // EXPRESSIONELEMET_H
