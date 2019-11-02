#include "transaction_parser.h"

TransactionParserInterface::TransactionParserInterface()
{

}

TransactionParserInterface::~TransactionParserInterface()
{

}

QList<Transaction> BNPTransactionParser::parseTransactions(QFile* file)
{
    QTextStream in(file);
    QList<Transaction> transactionsList;

    while(!in.atEnd())
    {
        QString fileLine = in.readLine();
        qDebug() << fileLine;
        QStringList lineToken = fileLine.split(";");

        if(lineToken.at(0) == "Completed Date")
        {
            continue;
        }

        Transaction transaction;
        QString date = lineToken.at(0);
        QDate qdate = QDate::fromString(date, "MMMM d");
        if(qdate.isValid())
        {
            //TODO fix current date
           date = qdate.toString(Qt::ISODate);
        }
        else
        {
           date = QDate::fromString(date, "yyyy MMMM d").toString(Qt::ISODate);
        }
        transaction.date = date;
        transaction.reference = lineToken.at(1);

        QString category = lineToken.at(7);
        category = category.remove(QChar(','), Qt::CaseInsensitive);
        transaction.category = category;

        QString paid_in = lineToken.at(3);
        QString paid_out = lineToken.at(2);
        double amount;
        if(paid_in == "")
        {
            //TODO automatically detect wheter . or ,
            amount = paid_out.replace(",", ".").toDouble();
        }
        else if (paid_out == "")
        {
            amount = paid_in.replace(",", ".").toDouble();
        }
        else{
            amount = 0;
            qDebug() << "Transaction has no value";
        }
        transaction.amount = amount;
        transactionsList.append(transaction);
    }

    return transactionsList;
}

