#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    BNPTransactionParser *BNPParser = new BNPTransactionParser;

    QFile BNP("/Users/chris/tutorial-1/revolute.csv");
    if(BNP.open(QIODevice::ReadOnly))
    {
        QList<Transaction> transcations = BNPParser->parseTransactions(&BNP);

        QList<Transaction>::iterator i;
        for (i = transcations.begin(); i != transcations.end(); ++i)
        {
            qDebug() << i->date;
            qDebug() << i->reference;
            qDebug() << i->category;
            qDebug() << i->amount;
        }

        BNP.close();
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

