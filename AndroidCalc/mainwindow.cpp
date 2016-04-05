#include "mainwindow.h"
#include "ui_mainwindow.h"
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setContextMenuPolicy(Qt::CustomContextMenu);
    text = new QListWidgetItem;
    text->setText("");
    equation = new QListWidgetItem;
    StringCalculator::setup();
   // parseableString = "1[+]1[-][sin](";
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
    parseableString.append("1");
}

void MainWindow::on_btnTwo_clicked()
{
    text->setText(text->text() + "2");
    ui->listDisplay->addItem(text);
    parseableString.append("2");
}

void MainWindow::on_btnThree_clicked()
{
    text->setText(text->text() + "3");
    ui->listDisplay->addItem(text);
    parseableString.append("3");
}


void MainWindow::on_btnFour_clicked()
{
    text->setText(text->text() + "4");
    ui->listDisplay->addItem(text);
    parseableString.append("4");
}


void MainWindow::on_btnFive_clicked()
{
    text->setText(text->text() + "5");
    ui->listDisplay->addItem(text);
    parseableString.append("5");
}


void MainWindow::on_btnSix_clicked()
{
    text->setText(text->text() + "6");
    ui->listDisplay->addItem(text);
    parseableString.append("6");
}


void MainWindow::on_btnSeven_clicked()
{
    text->setText(text->text() + "7");
    ui->listDisplay->addItem(text);
    parseableString.append("7");
}


void MainWindow::on_btnEight_clicked()
{
    text->setText(text->text() + "8");
    ui->listDisplay->addItem(text);
    parseableString.append("8");
}


void MainWindow::on_btnNine_clicked()
{
    text->setText(text->text() + "9");
    ui->listDisplay->addItem(text);
    parseableString.append("9");
}

void MainWindow::on_btnZero_clicked()
{
    text->setText(text->text() + "0");
    ui->listDisplay->addItem(text);
    parseableString.append("0");
}

void MainWindow::on_btnDot_clicked()
{
    text->setText(text->text() + ".");
    ui->listDisplay->addItem(text);
    parseableString.append(".");
}

void MainWindow::on_btnLeftPar_clicked()
{
    text->setText(text->text() + "(");
    ui->listDisplay->addItem(text);
    parseableString.append(MainWindow::addBrackets("(", false));
}

void MainWindow::on_btnRightPar_clicked()
{
    text->setText(text->text() + ")");
    ui->listDisplay->addItem(text);
     parseableString.append(MainWindow::addBrackets(")", false));
}

void MainWindow::on_btnPow_clicked()
{
    text->setText(text->text() + "^");
    ui->listDisplay->addItem(text);
     parseableString.append(MainWindow::addBrackets("^", false));
}

void MainWindow::on_btnDivide_clicked()
{
    text->setText(text->text() + "/");
    ui->listDisplay->addItem(text);
    parseableString.append(MainWindow::addBrackets("/", false));
}

void MainWindow::on_btnMultiply_clicked()
{
    text->setText(text->text() + "*");
    ui->listDisplay->addItem(text);
    parseableString.append(MainWindow::addBrackets("*", false));
}

void MainWindow::on_btnMinus_clicked()
{
    text->setText(text->text() + "-");
    ui->listDisplay->addItem(text);
    parseableString.append(MainWindow::addBrackets("-", false));
}

void MainWindow::on_btnPlus_clicked()
{
    text->setText(text->text() + "+");
    ui->listDisplay->addItem(text);
    parseableString.append(MainWindow::addBrackets("+", false));
}

void MainWindow::on_btnLog_clicked()
{
    text->setText(text->text() + "log(");
    ui->listDisplay->addItem(text);
    parseableString.append(MainWindow::addBrackets("log", false) + "(");
}

void MainWindow::on_btnLn_clicked()
{
    text->setText(text->text() + "ln(");
    ui->listDisplay->addItem(text);
    parseableString.append(MainWindow::addBrackets("ln", false) + "(");
}

void MainWindow::on_btnE_clicked()
{
    text->setText(text->text() + "e");
    ui->listDisplay->addItem(text);
    parseableString.append(MainWindow::addBrackets("e", true));
}

void MainWindow::on_btnPi_clicked()
{
    text->setText(text->text() + "pi");
    ui->listDisplay->addItem(text);
    parseableString.append(MainWindow::addBrackets("pi", true));
}

void MainWindow::on_btnFact_clicked()
{
    text->setText(text->text() + "!");
    ui->listDisplay->addItem(text);
    parseableString.append(MainWindow::addBrackets("!", true));
}

void MainWindow::on_btnSin_clicked()
{
    text->setText(text->text() + "sin(");
    ui->listDisplay->addItem(text);
    parseableString.append(MainWindow::addBrackets("sin", false) + "(");
}

void MainWindow::on_btnCos_clicked()
{
    text->setText(text->text() + "cos(");
    ui->listDisplay->addItem(text);
    parseableString.append(MainWindow::addBrackets("cos", false + "("));
}

void MainWindow::on_btnTan_clicked()
{
    text->setText(text->text() + "tan(");
    ui->listDisplay->addItem(text);
    parseableString.append(MainWindow::addBrackets("tan", false) + "(");
}

void MainWindow::on_btnnCm_clicked()
{
    text->setText(text->text() + "C");
    ui->listDisplay->addItem(text);
    parseableString.append(MainWindow::addBrackets("C", true));
}

void MainWindow::on_btnArcSin_clicked()
{
    text->setText(text->text() + "arcsin(");
    ui->listDisplay->addItem(text);
    parseableString.append(MainWindow::addBrackets("arcsin", false) + "(");
}

void MainWindow::on_btnArcCos_clicked()
{
    text->setText(text->text() + "arccos(");
    ui->listDisplay->addItem(text);
    parseableString.append(MainWindow::addBrackets("arccos", false) + "(");
}

void MainWindow::on_btnArcTan_clicked()
{
    text->setText(text->text() + "arctan(");
    ui->listDisplay->addItem(text);
    parseableString.append(MainWindow::addBrackets("arctan", false) + "(");
}

void MainWindow::on_btnnPm_clicked()
{
    text->setText(text->text() + "P");
    ui->listDisplay->addItem(text);
    parseableString.append(MainWindow::addBrackets("P", true));
}

void MainWindow::on_btnSinh_clicked()
{
    text->setText(text->text() + "sinh(");
    ui->listDisplay->addItem(text);
    parseableString.append(MainWindow::addBrackets("sinh", false) + "(");
}

void MainWindow::on_btnCosh_clicked()
{
    text->setText(text->text() + "cosh(");
    ui->listDisplay->addItem(text);
    parseableString.append(MainWindow::addBrackets("cosh", false) + "(");
}

void MainWindow::on_btnTanh_clicked()
{
    text->setText(text->text() + "tanh(");
    ui->listDisplay->addItem(text);
    parseableString.append(MainWindow::addBrackets("tanh", false) + "(");
}

void MainWindow::on_btnClear_clicked()
{
    text->setText("");
    parseableString.clear();
    ui->listDisplay->addItem(text);
}


void MainWindow::on_btnDegAndRad_clicked()
{
    if (units)
    {
        QMessageBox::information(this, "The Units Have Changed", "The trigometric values will now be outputed in Radians");
        units = false;
        //StringCalculator::useDegrees(false);
    }
    else
    {
        QMessageBox::information(this, "The Units Have Changed", "The trigometric values will now be outputed in Degrees");
        units = true;
        //StringCalculator::useDegrees(true);
    }
}

//End of Repetitive Button Code

QString MainWindow::addBrackets(QString symbol, bool special)
{
   QString newText = symbol;
   if (!special)
   {
   newText.insert(0, "[");
   newText.insert(newText.length() + 1, "]");
   return newText;
   }
   else
   {
       newText.insert(0, "([");
       newText.insert(newText.length() + 1, "])");
       return newText;
   }
}

void MainWindow::on_btnEval_clicked()
{
    if (!text->text().isEmpty())
    {
        try
        {
            equation->setText(text->text());
            //Debug Message to show what's going into the "engine"
            QMessageBox::information(this, "New String:", parseableString);
            value = StringCalculator::calculateQStringInput(parseableString);
            //Int to QString Conversion
            QString result = QString::number(value);
            items.append(equation->text());
            items.append("=" + result);
            ui->listDisplay->addItems(items);
            /*Since I was unable to get the loop to work to make sure it didn't print multiple times,
              I had to clear the list right after it prints. It doesn't work when just equation is
              printed, but it works with the list for whatever reason.
              The good news is that the QListWidget should theoretically still hold all of the values.*/

            //Reset the calculator, and set the new line on the calculator
            items.clear();
            text->setText("");
            ui->listDisplay->setCurrentRow(ui->listDisplay->currentRow() + 2);
            ui->listDisplay->takeItem(ui->listDisplay->row(text));
            ui->listDisplay->item(ui->listDisplay->count() - 1)->setSelected(true);
            ui->listDisplay->setFocus();
            parseableString.clear();
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
                case 103:
                    QMessageBox::information(this, "Error", "While this may or may not be acceptable in mathematical notation,\n"
                                                            "this calculator does not support this.");
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
    else
    {
        QMessageBox::information(this, "Nothing to Do", "There is no text detected on the screen.");
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
    QString ref = newText.right(newText.length() - 3);
    QMessageBox::information(this, "ref", ref);
    if (!text->text().isEmpty() &&  !parseableString.isEmpty())
    {

    if (!parseableString.isEmpty() && newText.at(newText.length() -1) != 'e' && ref != "pi" && newText.at(newText.length() -1) != '!' && newText.at(newText.length() -1) != 'C' && newText.at(newText.length() -1) != 'P')
    {
    QMessageBox::information(this, "New String:", parseableString);

    int firstMark = -1;
        if (parseableString.at(parseableString.length() - 1) == ']')
        {
            int chopCount = 0;
            for(int i = parseableString.length() - 1; i >= 0; i--)
            {
                if (parseableString.at(i) == ']')
                {
                    firstMark = parseableString.indexOf(parseableString.at(i));
                }
                else if (parseableString.at(i) == '[' && firstMark >= 0)
                {
                    chopCount++;
                    break;
                }

                if(firstMark >= 0)
                {
                    chopCount++;
                }

            }
            QStringRef removeText = newText.rightRef(chopCount - 3);
            QChar symbolCheck = removeText.toString().at(removeText.toString().length() - 1);
            parseableString.chop(chopCount);
            QMessageBox::information(this, "Text to be removed", removeText.toString());
            if (symbolCheck.isSymbol() || symbolCheck.isPunct())
            {
                QMessageBox::warning(this, "Triggered", "Contains Symbol");
                newText.chop(1);
                text->setText(newText);
                ui->listDisplay->addItem(text);
            }
            else
            {
                newText.chop(removeText.length());
                text->setText(newText);
                ui->listDisplay->addItem(text);
            }

        }
        else
        {
            parseableString.chop(1);
            newText.chop(1);
            text->setText(newText);
            ui->listDisplay->addItem(text);
        }
    }

    else if (newText.at(newText.length() - 1) == 'e' || newText.at(newText.length() - 1) == '!' || newText.at(newText.length() - 1) == 'C' || newText.at(newText.length() - 1) == 'P')
    {
        parseableString.chop(6);
        newText.chop(1);
        text->setText(newText);
        ui->listDisplay->addItem(text);
    }
    else if (ref == "pi")
    {
        parseableString.chop(7);
        newText.chop(2);
        text->setText(newText);
        ui->listDisplay->addItem(text);
    }
    }
    else if (newText.isEmpty() && !parseableString.isEmpty())
    {
        parseableString.clear();
    }

}

//Makes the history finite
void MainWindow::on_listDisplay_currentRowChanged(int currentRow)
{
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
    QString history = ui->listDisplay->item(index.row())->text();
    if (history.contains("="))
    {
        history.remove(0, 1);
    }
    text->setText(text->text() + history);
    ui->listDisplay->addItem(text);
}

void MainWindow::on_btnSci_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}


void MainWindow::on_btnBack_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}

void MainWindow::on_btnSciEqual_clicked()
{
    ui->btnEval->click();
}

