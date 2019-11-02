#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    RevoluteTransactionParser *RevoluteParser = new RevoluteTransactionParser;

    QFile Revolute("/Users/chris/tutorial-1/revolute.csv");
    if(Revolute.open(QIODevice::ReadOnly))
    {
        QList<Transaction> transcations = RevoluteParser->parseTransactionList(&Revolute);

        QList<Transaction>::iterator i;
        for (i = transcations.begin(); i != transcations.end(); ++i)
        {
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

