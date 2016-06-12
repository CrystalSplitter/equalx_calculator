#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QListWidgetItem>
#include <QMessageBox>
#include <QRegExp>
#include <QMenu>
#include <QAction>
#include "expressionelement.h"
#include "stringcalculator.h"
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT


public:
    explicit MainWindow(QWidget *parent = 0);
    enum Operation{none, add, sub, multi, div, powa}; // The types of operations available on this calculator
    enum ExpressionElemType{number,operation};
    ~MainWindow();

private slots:
    void on_btnOne_clicked();

    void on_btnTwo_clicked();

    void on_btnThree_clicked();

    void on_btnFour_clicked();

    void on_btnFive_clicked();

    void on_btnSix_clicked();

    void on_btnSeven_clicked();

    void on_btnEight_clicked();

    void on_btnNine_clicked();

    void on_btnZero_clicked();

    void on_btnDot_clicked();

    void on_btnLeftPar_clicked();

    void on_btnRightPar_clicked();

    void on_btnPow_clicked();

    void on_btnDivide_clicked();

    void on_btnMultiply_clicked();

    void on_btnMinus_clicked();

    void on_btnPlus_clicked();

    void on_btnEval_clicked();

    void on_btnAnswer_clicked();

    void on_btnDelete_clicked();

    void on_listDisplay_currentRowChanged(int currentRow);

    void on_listDisplay_doubleClicked(const QModelIndex &index);

    void on_btnSci_clicked();

    void on_btnBack_clicked();

    void on_btnLog_clicked();

    void on_btnLn_clicked();

    void on_btnE_clicked();

    void on_btnPi_clicked();

    void on_btnFact_clicked();

    void on_btnSin_clicked();

    void on_btnCos_clicked();

    void on_btnTan_clicked();

    void on_btnnCm_clicked();

    void on_btnArcSin_clicked();

    void on_btnArcCos_clicked();

    void on_btnArcTan_clicked();

    void on_btnnPm_clicked();

    void on_btnSinh_clicked();

    void on_btnCosh_clicked();

    void on_btnTanh_clicked();

    void on_btnSciEqual_clicked();

    QString addBrackets(QString symbol, bool special);

    void on_btnClear_clicked();

    void on_btnDegAndRad_clicked();

private:
    Ui::MainWindow *ui;
protected:
    QListWidgetItem *text; // User input before it is put into the history
    QListWidgetItem *equation; //The finalized equation
    QList<QString> items; //How it gets printed pretty much
    double value; //Answer
    QString parseableString; //blah
    bool units = false; //False = Radians, Degrees = True
};

#endif // MAINWINDOW_H
