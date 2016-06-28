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
    ui->btnPi->setText("\u03c0");
    equation = new QListWidgetItem;
    StringCalculator::setup();
}

// Main Window Destructor
//  Removes the UI when the application closes.
MainWindow::~MainWindow()
{
    delete ui;
}

// TODO:
// Make these all the same function with different arguments. Same name.
// Repetitive Button Code
void MainWindow::on_btnOne_clicked() { MainWindow::inputButtonClicked("1", false, false); }
void MainWindow::on_btnTwo_clicked() { MainWindow::inputButtonClicked("2", false, false); }
void MainWindow::on_btnThree_clicked() { MainWindow::inputButtonClicked("3", false, false); }
void MainWindow::on_btnFour_clicked() { MainWindow::inputButtonClicked("4", false, false); }
void MainWindow::on_btnFive_clicked() { MainWindow::inputButtonClicked("5", false, false); }
void MainWindow::on_btnSix_clicked() { MainWindow::inputButtonClicked("6", false, false); }
void MainWindow::on_btnSeven_clicked() { MainWindow::inputButtonClicked("7", false, false); }
void MainWindow::on_btnEight_clicked() { MainWindow::inputButtonClicked("8", false, false); }
void MainWindow::on_btnNine_clicked() { MainWindow::inputButtonClicked("9", false, false); }
void MainWindow::on_btnZero_clicked() { MainWindow::inputButtonClicked("0", false, false); }
void MainWindow::on_btnDot_clicked() { MainWindow::inputButtonClicked(".", false, false); }
void MainWindow::on_btnLeftPar_clicked() { MainWindow::inputButtonClicked("(", false, false); }
void MainWindow::on_btnRightPar_clicked() { MainWindow::inputButtonClicked(")", false, false); }
void MainWindow::on_btnPow_clicked() { MainWindow::inputButtonClicked("^", true, false); }
void MainWindow::on_btnDivide_clicked() { MainWindow::inputButtonClicked("/", true, false); }
void MainWindow::on_btnMultiply_clicked() { MainWindow::inputButtonClicked("*", true, false); }
void MainWindow::on_btnMinus_clicked() { MainWindow::inputButtonClicked("-", true, false); }
void MainWindow::on_btnPlus_clicked() { MainWindow::inputButtonClicked("+", true, false); }
void MainWindow::on_btnLog_clicked() { MainWindow::inputButtonClicked("log", true, true); }
void MainWindow::on_btnLn_clicked() { MainWindow::inputButtonClicked("ln", true, true); }
void MainWindow::on_btnE_clicked() { MainWindow::inputButtonClicked("e", true, false); }
void MainWindow::on_btnPi_clicked() { MainWindow::inputButtonClicked("pi", true, false); }
void MainWindow::on_btnFact_clicked() { MainWindow::inputButtonClicked("!", true, false); }
void MainWindow::on_btnSin_clicked() { MainWindow::inputButtonClicked("sin", true, true); }
void MainWindow::on_btnCos_clicked() { MainWindow::inputButtonClicked("cos", true, true); }
void MainWindow::on_btnTan_clicked() { MainWindow::inputButtonClicked("tan", true, true); }
void MainWindow::on_btnnCm_clicked() { MainWindow::inputButtonClicked("C", true, false); }
void MainWindow::on_btnnPm_clicked() { MainWindow::inputButtonClicked("P", true, false); }
void MainWindow::on_btnArcSin_clicked() { MainWindow::inputButtonClicked("asin", true, true); }
void MainWindow::on_btnArcCos_clicked() { MainWindow::inputButtonClicked("acos", true, true); }
void MainWindow::on_btnArcTan_clicked() { MainWindow::inputButtonClicked("atan", true, true); }
void MainWindow::on_btnSinh_clicked() { MainWindow::inputButtonClicked("sinh", true, true); }
void MainWindow::on_btnCosh_clicked() { MainWindow::inputButtonClicked("cosh", true, true); }
void MainWindow::on_btnTanh_clicked() { MainWindow::inputButtonClicked("tanh", true, true); }
void MainWindow::on_btnClear_clicked() { parseableString.clear(); }
void MainWindow::on_btnSciClear_clicked(){parseableString.clear();}
void MainWindow::on_btnSciDelete_clicked(){ui->btnDelete->click();}
void MainWindow::on_btnDegAndRad_clicked()
{
    if(useDegrees)
    {
        QMessageBox::information(this, "The Units Have Changed", "The trigometric values will now be outputed in Radians");
        useDegrees = false;
        //StringCalculator::useDegrees(false);
    }
    else
    {
        QMessageBox::information(this, "The Units Have Changed", "The trigometric values will now be outputed in Degrees");
        useDegrees = true;
        //StringCalculator::useDegrees(true);
    }
}

void MainWindow::inputButtonClicked(QString input, bool addBrackets, bool appendOpenParen)
{
    QString appendedString = (addBrackets) ? MainWindow::addBrackets(input) : input;
    if(appendOpenParen) { appendedString += "(&"; }
    parseableString += appendedString;
    updateRenderInput();
}

// updateRenderInput()
//      Updates the calculator's input field to represent the parseableString.
void MainWindow::updateRenderInput()
{
    text->setText(InputRenderer::render(parseableString));
    ui->listDisplay->addItem(text);
}

// End of Repetitive Button Code

// The parseable string needs brackets to differentiate different functions and operations, and also for the special cases of e and pi.
QString MainWindow::addBrackets(QString input)
{
   QString output = input;
   output.insert(0, "[");
   output.append("]");
   return output;
}

void MainWindow::on_btnEval_clicked()
{
    if(!text->text().isEmpty())
    {
        try
        {
            equation->setText(text->text());
            // Debug Message to show what's going into the "engine"
            QMessageBox::information(this, "New String:", parseableString);
            value = StringCalculator::calculateQStringInput(parseableString);
            // Int to QString Conversion
            QString result;
            result = QString::number(value);

            // Scientific notation for both large numbers and decimals
            if(QString::number(value).length() >= 10)
            {
                if(value > 10000000000)
                {
                    value = value/10;
                    result = QString::number(value);
                }
                else
                {
                    value = pow(10, value);
                    result = QString::number(value) + "e-" + QString::number(equation->text().length());
                }
            }

            // Append results to screen
            items.append(equation->text());
            items.append("= " + result);
            ui->listDisplay->addItems(items);

            /*
             * Since I was unable to get the loop to work to make sure it didn't print multiple times,
             * I had to clear the list right after it prints. It doesn't work when just equation is
             * printed, but it works with the list for whatever reason.
             * The good news is that the QListWidget should theoretically still hold all of the values.
             */

            // Reset the calculator, and set the new line on the calculator
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
                case 203:
                    QMessageBox::information(this, "Error", "An operation you entered had invalid arguments.");
                break;
                case 204:
                    QMessageBox::information(this, "Error", "Your answer was larger than a googol. which is not something our calculator can account for.");
                default:
                    QMessageBox::information(this, "Wow", "Look, we have an error for everything we could resonably expect and even unexpect.\n"
                                                          "You managed to do something beyond the unexpected. You're one of those people who thinks"
                                                          "that nothing fits within a binary. We expected a 0 or a 1, and you gave us a 2.\n"
                                                          "Just props to you man.");
                break;
            }
        }
    }
}

// Grabs the last line to be used as the answer.
void MainWindow::on_btnAnswer_clicked()
{
    if(ui->listDisplay->count() > 1)
    {
        //text->setText(text->text() + QString::number(value));
        MainWindow::inputButtonClicked(QString::number(value), false, false);
        //ui->listDisplay->addItem(text);
    }
    else
    {
        QMessageBox::information(this, "No History", "Can not append history to current calculation. No history exists.");
    }
}

void MainWindow::on_btnDelete_clicked()
{
    if(!parseableString.isEmpty())
    {
        int lastCharIndex = parseableString.length() - 1;
        int openBracketIndex = -1;
        if(parseableString.at(lastCharIndex) == ']'
                || parseableString.at(lastCharIndex) == '&' )
        {
            for(int i = lastCharIndex; i >= 0; i--)
            {
                if(parseableString.at(i) == '[')
                {
                    openBracketIndex = i;
                    break;
                }
            }
            parseableString.chop(lastCharIndex - openBracketIndex + 1);
        }
        else
        {
            parseableString.chop(1);
        }

        MainWindow::updateRenderInput();
    }
}

// Makes the history finite
void MainWindow::on_listDisplay_currentRowChanged(int currentRow)
{
    if(currentRow > 50)
    {
        for (int i = 0; i <= 10; i++)
        {
            ui->listDisplay->takeItem(i);
        }
    }
}

// Grabs the history
void MainWindow::on_listDisplay_doubleClicked(const QModelIndex &index)
{
    // Old Debug Message to try and figure out whether the method was being triggered or not.
    //MessageBox::information(this, "It worked.", "Yay! :D");
    QString history = ui->listDisplay->item(index.row())->text();
    if(history.contains("="))
    {
        history.remove(0, 1);
    }
    text->setText(text->text() + history);
    ui->listDisplay->addItem(text);
}

// Changes over the index of buttons to the function page
void MainWindow::on_btnSci_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}

// Goes Back to the main screen
void MainWindow::on_btnBack_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}

// Rather than repeat all the code, I just trigger the button on the first page to be hit
void MainWindow::on_btnSciEqual_clicked()
{
    ui->btnEval->click();
}
