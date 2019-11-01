#include "transaction_parser.h"

TransactionParserInterface::TransactionParserInterface()
{

}

TransactionParserInterface::~TransactionParserInterface()
{

}

QStringList BNPTransactionParser::parseTransactions(QFile* file)
{
    QTextStream in(file);
    while(!in.atEnd())
    {
        QString fileLine = in.readLine();
        QStringList lineToken = fileLine.split(";");
        qDebug() << lineToken;
    }
    QStringList transaction;
    return transaction;
}

