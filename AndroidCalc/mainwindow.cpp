#include "mainwindow.h"
#include "ui_mainwindow.h"
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    text = new QListWidgetItem;
    text->setText("");
    equation = new QListWidgetItem;
    StringCalculator::setup();
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
    try
    {
        equation->setText(text->text());
        QString blah = text->text();
        value = StringCalculator::calculateCharVector(StringCalculator::convertToVector(blah));
        QString result = QString::number(value);
        items.append(equation->text());
        items.append(result);
        ui->listDisplay->addItems(items);
        /*Since I was unable to get the loop to work to make sure it didn't print multiple times,
          I had to clear the list right after it prints. It doesn't work when just equation is
          printed, but it works with the list for whatever reason.
          The good news is that the QListWidget should theoretically still hold all of the values.*/
        items.clear();
        text->setText("");
        ui->listDisplay->setCurrentRow(ui->listDisplay->currentRow() + 2);
        ui->listDisplay->takeItem(ui->listDisplay->row(text));
        ui->listDisplay->item(ui->listDisplay->count() - 1)->setSelected(true);
        ui->listDisplay->setFocus();
    }
    catch(int e)
    {
        switch (e)
        {
            case 100:
                QMessageBox::information(this, "Error", "Syntax Error");
            break;
            case 101:
                QMessageBox::information(this, "Error", "The input ended in an operation.");
            break;
            case 102:
                QMessageBox::information(this, "Error", "A parenthesis is missing.");
            break;
            case 200:
                QMessageBox::information(this, "Error", "Unfortunately, the calculator did not know how to handle this calculation.");
            break;
            case 201:
                QMessageBox::information(this, "Error", "You inputed something the calculator could not expect. Well done!");
            break;
            default:
                QMessageBox::information(this, "Wow", "Look, we have an error for everything we could resonably expect and even unexpect.\n"
                                                      "You managed to do something beyond the unexpected. You're one of those people who thinks"
                                                      "that nothing fits within a binary. We expected a 0 or a 1, and you gave us a 2.\n"
                                                      "Just props to you man.");
            break;
        }
    }
}

void MainWindow::on_btnAnswer_clicked()
{
    if (ui->listDisplay->count() > 1)
    {
        text->setText(text->text() + QString::number(value));
        ui->listDisplay->addItem(text);
    }
    else
    {
        QMessageBox::information(this, "No History", "Can not append history to current calculation. No history exists.");
    }
}

void MainWindow::on_btnDelete_clicked()
{
    QString newText = text->text();
    newText.chop(1);
    text->setText(newText);
    ui->listDisplay->addItem(text);
}

//Makes the history finite
void MainWindow::on_listDisplay_currentRowChanged(int currentRow)
{
    //TODO: Check to make sure currentRow works
    if (currentRow > 50)
    {
        for (int i = 0; i <= 10; i++)
        {
            ui->listDisplay->takeItem(i);
        }
    }
}

void MainWindow::on_listDisplay_doubleClicked(const QModelIndex &index)
{
    QMessageBox::information(this, "It worked.", "Yay! :D");
    text->setText(text->text() + ui->listDisplay->item(index.row())->text());
    ui->listDisplay->addItem(text);
}

void MainWindow::on_btnSci_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}

void MainWindow::displayError()
{

}


void MainWindow::on_btnBack_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}
