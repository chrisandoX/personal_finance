#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QString database_path = "/Users/chris/personal_finance_app/personal_finanace/phinance.db";
    DbManager db(database_path);

    if (db.isOpen())
    {
        db.createTable();
    }
    else
    {
        qDebug() << "Database is not open!";
    }


    RevoluteTransactionParser *RevoluteParser = new RevoluteTransactionParser;

    QFile Revolute("/Users/chris/personal_finance_app/personal_finanace/revolute.csv");
    if(!Revolute.open(QIODevice::ReadOnly))
    {
        qDebug() << "File not found";
        return;
    }

    BNPTransactionParser *BNPParser = new BNPTransactionParser;

    QFile BNP("/Users/chris/personal_finance_app/personal_finanace/bnp.csv");
    if(!BNP.open(QIODevice::ReadOnly))
    {
        qDebug() << "File not found";
        return;
    }


    QList<Transaction> transcations;
    try
    {
        transcations.append(BNPParser->parseTransactionList(&BNP));
        transcations.append(RevoluteParser->parseTransactionList(&Revolute));
        BNP.close();
        Revolute.close();
    }
    catch (const char* exception) // catch exceptions of type const char*
    {
       qDebug() << "Error: " << exception;
    }

    QList<Transaction>::iterator i;
    for (i = transcations.begin(); i != transcations.end(); ++i)
    {
        if(db.isOpen())
        {
            db.addTransaction(*i);
        }
        else
        {
            qDebug() << "Database is not open!";
        }
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

