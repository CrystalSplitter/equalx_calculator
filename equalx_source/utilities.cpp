#include <QApplication>
#include <QDebug>

#include "utilities.h"

/*
 * convertToVector:
 *
 * Converts a QString to a char QVector.
 */
QVector<char> Utilities::convertToVector(QString s)
{
    QVector<char> newVector = QVector<char>(s.length());
    for(int i = 0; i < s.length(); i++)
    {
        newVector[i] = s.at(i).toLatin1();
    }
    return newVector;
}

/*
 * vectorComparison
 *
 */
bool Utilities::vectorComparison(QVector<char> toCompare, QVector<char> match)
{
    for(int i = 0; i < std::max(match.size(), toCompare.size()); i++)
    {
        if(i >= toCompare.size())
            return false; // Reached end of toCompare

        if(i >= match.size())
            return false; // Return false

        if(match[i] != toCompare[i])
            return false; // Not equal, return false
    }
    return true; // Everything matched! Good to go.
}

QString Utilities::betterVectorPrint(QVector<char> v)
{
    qDebug() << "V[";
    for(int i = 0; i < v.size(); i++)
    {
        qDebug() << v[i] << ",";
    }
    qDebug() << "]";
}


QString Utilities::betterVectorPrint(ExpressionElement* v)
{
    QString msg = QString("");
    msg.append("V[");
    for()
    {
        msg.append(e.toString() + ",");
    }
    msg.append("]");
    qDebug() << msg;
}

/*
 *
 *
 */
Operation::Enum Utilities::convertVectorToOP(QVector<char> v)
{

}
