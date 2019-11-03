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
    if(Revolute.open(QIODevice::ReadOnly))
    {

        QList<Transaction> transcations;
        try
        {
            transcations = RevoluteParser->parseTransactionList(&Revolute);
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

        Revolute.close();
    }
    else
    {
        qDebug() << "File not found";
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

