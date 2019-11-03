#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QString database_name = "/Users/chris/personal_finance_app/personal_finanace/phinance.db";

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
            QSqlQuery query;
            query.prepare("INSERT INTO transactions(date, title, amount, category) "
                           "VALUES (:date, :title, :amount, :category)");
            query.bindValue(":date", i->date);
            query.bindValue(":title", i->reference);
            query.bindValue(":amount", i->amount);
            query.bindValue(":category", i->category);

            if(!query.exec())
                qDebug()<<query.lastError();

            qDebug() << i->date << i->reference << i->amount << i->category;
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

