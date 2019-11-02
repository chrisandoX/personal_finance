#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QString database_name = "/Users/chris/personal_finance_app/personal_finanace/phinance.db";

    if(!QFile::exists(database_name))
        qDebug() << "Database file does not exists";
    else{
        QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
        db.setDatabaseName(database_name);
        if(!db.open())
          qDebug() << "Failed to open database";
        else
          qDebug() << "Database opened";
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
            query.exec();
            qDebug()<<query.lastError();

            qDebug() << i->date;
            qDebug() << i->reference;
            qDebug() << i->category;
            qDebug() << i->amount;
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

