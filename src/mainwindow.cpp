#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , db("phinance.db")
    , ui(new Ui::MainWindow)

{
    ui->setupUi(this);
    ui->dateFrom->setCalendarPopup(true);
    ui->dateFrom->setDate(QDate::currentDate());
    ui->dateFrom->setDisplayFormat("yyyy.MM.dd");

    ui->dateUntil->setCalendarPopup(true);
    ui->dateUntil->setDate(QDate::currentDate());
    ui->dateUntil->setMaximumDate(QDate::currentDate());
    ui->dateUntil->setDisplayFormat("yyyy.MM.dd");


}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    QMessageBox msgBox;
    qDebug() << "Selecting the file";
    QFileDialog dialog(this);
    dialog.setFileMode(QFileDialog::ExistingFile);
    dialog.setViewMode(QFileDialog::Detail);
    dialog.setNameFilter(tr("CSV (*.csv)"));
    QStringList fileNames;
    if (dialog.exec()) {
        fileNames = dialog.selectedFiles();
    }
    else
        return;
    qDebug() << fileNames;

    if (db.isOpen())
    {
        db.createTable();
    }
    else
    {
        qDebug() << "Database is not open!";
    }

    QFile file(fileNames[0]);
    if(!file.open(QIODevice::ReadOnly))
    {
        qDebug() << "File not found";
        return;
    }

    TransactionParser *Parser = new TransactionParser;

    QList<Transaction> transcations;
    try
    {
        transcations.append(Parser->parseTransactionFile(&file));
    }
    catch (const char* exception)
    {
       qDebug() << "Error: " << exception;
    }

    QList<Transaction>::iterator i;
    for (i = transcations.begin(); i != transcations.end(); ++i)
    {
        if(db.isOpen())
        {
            if(!db.addTransaction(*i)){
                qDebug() << "Failed to load transaction" << i->reference;
            }
        }
        else
        {
            qDebug() << "Database is not open!";
        }
    }
    msgBox.setText("All transactions loaded");
    msgBox.exec();
    file.close();
}


void MainWindow::on_dateFrom_userDateChanged(const QDate &date)
{
    date_from = date;
}

void MainWindow::on_dateUntil_userDateChanged(const QDate &date)
{
    ui->dateFrom->setMaximumDate(date);
    date_until = date;
    qDebug() << date_from << "\n" << date_until;
}

void MainWindow::on_pushButtonShowSelectedTransactions_clicked()
{
    tableModel = db.getTransactionsTableInRange(date_from, date_until);
    QTableView *view = new QTableView;
    view->setModel(tableModel);
    view->hideColumn(0); // don't show the ID
    view->show();
}
