#include "unittester.h"

// This is a unit testing suite for the equalx calculator.
// It should not be packaged along with the actual application.

UnitTester::UnitTester(int accuracy, bool showSuccess)
{
    accuracy_ = accuracy;
    errorbar_ = pow(10.0, -accuracy);
    showSuccess_ = showSuccess;
}

// assertEqual(double expression, double expected)
//      Checks to see if the expression and the expected output are equal.
//      If they are not, print a qCritical message.
int UnitTester::assertEqual(QString name, double result, double expected)
{
    // Throwaway reference
    int n1;
    int n2;

    double resultSig = /*frexp(result, &n1);*/ result;
    double expectedSig = /*frexp(expected, &n2);*/ expected;
    double diff = std::abs(resultSig - expectedSig);
    if(diff > errorbar_)
    {
        qCritical() << qSetRealNumberPrecision(accuracy_+2) << name << "FAILURE:" << "\n    Expected:" << expectedSig << "\n    Received:" << resultSig << "\n    Diff:" << diff;
        return 1;
    }
    else if(showSuccess_)
    {
        qDebug() << name << "passed.";
    }
    return 0;
}
