#include <QApplication>
#include <QDebug>

#include "mainwindow.h"
#include "expressionelement.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //MainWindow w;
    //w.show();

    try
    {
        qDebug() << ExpressionElement("[Hello World!]").toString();
    }
    catch (int e)
    {
        qDebug() << "There was an error: Error Num" << e << '\n';
    }

    return 0;
    //return a.exec();
}
