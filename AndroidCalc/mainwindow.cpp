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
    QString result = "Sample_Text"; //Serves as the placeholder for an actual calculation.
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
