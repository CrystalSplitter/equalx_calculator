#ifndef UNITTESTER_H
#define UNITTESTER_H

#include <QApplication>
#include <QDebug>
#include <cmath>

class UnitTester
{
private:
    int accuracy_;
    double errorbar_;
    bool showSuccess_ = false;

public:
    UnitTester(int accuracy, bool showSuccess);
    int assertEqual(QString name, double result, double expected);
};

#endif // UNITTESTER_H
