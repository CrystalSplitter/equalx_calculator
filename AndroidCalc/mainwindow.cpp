#include "mainwindow.h"
#include "ui_mainwindow.h"
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),     OP_ORDER{powa, multi, div, add, sub},
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    text = new QListWidgetItem;
    text->setText("");
    equation = new QListWidgetItem;
}

MainWindow::~MainWindow()
{
    delete ui;
}
// Repetitive Button Code
void MainWindow::on_btnOne_clicked()
{
    text->setText(text->text() + "1");
    ui->listDisplay->addItem(text);
}

void MainWindow::on_btnTwo_clicked()
{
    text->setText(text->text() + "2");
    ui->listDisplay->addItem(text);
}

void MainWindow::on_btnThree_clicked()
{
    text->setText(text->text() + "3");
    ui->listDisplay->addItem(text);
}


void MainWindow::on_btnFour_clicked()
{
    text->setText(text->text() + "4");
    ui->listDisplay->addItem(text);
}


void MainWindow::on_btnFive_clicked()
{
    text->setText(text->text() + "5");
    ui->listDisplay->addItem(text);
}


void MainWindow::on_btnSix_clicked()
{
    text->setText(text->text() + "6");
    ui->listDisplay->addItem(text);
}


void MainWindow::on_btnSeven_clicked()
{
    text->setText(text->text() + "7");
    ui->listDisplay->addItem(text);
}


void MainWindow::on_btnEight_clicked()
{
    text->setText(text->text() + "8");
    ui->listDisplay->addItem(text);
}


void MainWindow::on_btnNine_clicked()
{
    text->setText(text->text() + "9");
    ui->listDisplay->addItem(text);
}

void MainWindow::on_btnZero_clicked()
{
    text->setText(text->text() + "0");
    ui->listDisplay->addItem(text);
}

void MainWindow::on_btnDot_clicked()
{
    text->setText(text->text() + ".");
    ui->listDisplay->addItem(text);
}

void MainWindow::on_btnLeftPar_clicked()
{
    text->setText(text->text() + "(");
    ui->listDisplay->addItem(text);
}

void MainWindow::on_btnRightPar_clicked()
{
    text->setText(text->text() + ")");
    ui->listDisplay->addItem(text);
}

void MainWindow::on_btnPow_clicked()
{
    text->setText(text->text() + "^");
    ui->listDisplay->addItem(text);
}

void MainWindow::on_btnDivide_clicked()
{
    text->setText(text->text() + "/");
    ui->listDisplay->addItem(text);
}

void MainWindow::on_btnMultiply_clicked()
{
    text->setText(text->text() + "*");
    ui->listDisplay->addItem(text);
}

void MainWindow::on_btnMinus_clicked()
{
    text->setText(text->text() + "-");
    ui->listDisplay->addItem(text);
}

void MainWindow::on_btnPlus_clicked()
{
    text->setText(text->text() + "+");
    ui->listDisplay->addItem(text);
}
//End of Repetitive Button Code


void MainWindow::on_btnEval_clicked()
{

    /* Though this sounds like it would have worked,
       and it would have allowed for a more readable history that could be manipulated,
       it did not work for some undeterminable reason.
    bool identical;
    for(int i = 0; i < ui->listDisplay->count(); i++)
    {
        for (int j = 0; j <items.size(); j++)
        {
            if (items.at(j) == ui->listDisplay->item(i)->text())
                identical = true;
        }
        if (!identical)
            ui->listDisplay->addItem(ui->listDisplay->item(i));
    }*/
    /*It did not like it when I tried to append the original item "text"
      to the list so I made a new variable. I don't like it either.*/
    equation->setText(text->text());
    QByteArray data = equation->text().toUtf8();
    char* array = data.data();
    items.append(equation->text());
    double value = calculateCharArray(array);
    QString result = QString::number(value); //Serves as the placeholder for an actual calculation.
    items.append(result);
    ui->listDisplay->addItems(items);
    /*Since I was unable to get the loop to work to make sure it didn't print multiple times,
      I had to clear the list right after it prints. It doesn't work when just equation is
      printed, but it works with the list for whatever reason.
      The good news is that the QListWidget should theoretically still hold all of the values.*/
    items.clear();
    text->setText("");
    ui->listDisplay->setCurrentRow(ui->listDisplay->currentRow() + 1);
    ui->listDisplay->takeItem(ui->listDisplay->row(text));
    ui->listDisplay->item(ui->listDisplay->count() - 1)->setSelected(true);
    ui->listDisplay->setFocus();
}

//Makes the history finite
void MainWindow::on_listDisplay_currentRowChanged(int currentRow)
{
    if (ui->listDisplay->count() > 50)
    {
        for (int i = 0; i <= 10; i++)
        {
            ui->listDisplay->takeItem(i);
        }
    }
}


/* Any invocation of ExpressionElement results in the program blowing up. Do not touch until Crystal arrives.
QList<ExpressionElement> MainWindow::generateList(char* a)
{
    QList<ExpressionElement*> newList;
    QRegExp regex("[0-9]");
    bool grabbingSubExpression, grabbingNumber;
    int subExpressionStartingIndex = -1, numberStartingIndex = -1, numberEndingIndex = -1;
    for (int i = 0; i < sizeof(a); i++)
    {
        if (a[i] == '(')
        {
            grabbingSubExpression = true;
            subExpressionStartingIndex = i + 1;
            continue;
        }
        else if (a[i] == ')')
        {
            if(grabbingSubExpression)
            {
                grabbingSubExpression = false;
                char* subExpressionCharArray;
                for (int j = subExpressionStartingIndex; j < i; j++)
                {
                    subExpressionCharArray[j] = a[j];
                }

            }
        }
        else
        {
            QMessageBox::warning(this, "Whut", "Error");
        }
        if (grabbingSubExpression)
        {
            continue;
        }
        bool isNumber = regex.exactMatch(QString(a[i])), isPoint = (a[i] == '.');
        if (i == sizeof(a) - 1 && (!isNumber && !isPoint))
        {
             displayError();
             break;
        }
        if ((isNumber || isPoint) && i != sizeof(a) - 1)
        {
            if (!grabbingNumber)
            {
                numberStartingIndex = i;
                grabbingNumber = true;
            }
            continue;
        }
        else if(grabbingNumber)
        {
            grabbingNumber = false;
            if (i == sizeof(a) - 1)
            {
                numberEndingIndex = i + 1;
                char* newA;
                for (int j = numberStartingIndex; j < numberEndingIndex; j++)
                {
                    newA[j] = a[j];
                }
                newList.append(new ExpressionElement(newA, this));
                break;
            }
            else
            {
                char* newA;
                for (int j = numberStartingIndex; j < numberEndingIndex; j++)
                {
                    newA[j] = a[j];
                }
                newList.append(new ExpressionElement(newA, this));
            }
        }
        newList.append(new ExpressionElement(a[i],this));
    }

}
*/

ExpressionElement* MainWindow::listCalculation(QList<ExpressionElement*> elements)
{
    QList<ExpressionElement*> newList = elements;
    if (elements.at(0)->type == operation)
    {
        ExpressionElement* zeroElement = new ExpressionElement((double)0);
        newList.replace(0, zeroElement);
    }
    if (newList.size() == 2)
    {
        displayError();
    }
    for(Operation e: OP_ORDER)
    {
        int opCount = 0;
        for (int i = 0; i < newList.size(); i++)
        {
            if (newList.at(i)->type == operation)
            {
                if (newList.at(i)->op == e)
                    opCount++;
            }
        }
        while (opCount > 0)
        {
            int i = 0;
            while (i < newList.size()-2)
            {
                ExpressionElement *elem = newList.at(i + 1);
                if(elem->type == operation)
                {
                    double eval = elem->calc(newList.at(i),newList.at(i + 2));
                    newList.replace(i, new ExpressionElement(eval, this));
                    newList.removeAt(i + 2);
                    newList.removeAt(i + 1);
                    opCount--;
                }
            }
            i++;
        }
    }
    return newList.at(0);
}

double MainWindow::calculateCharArray(char *a)
{
    double value = 0;
    //QList<ExpressionElement> expressionList = generateList(a);
    //value = listCalculation(expressionList)->value;
    return value;
}

void MainWindow::displayError()
{

}
