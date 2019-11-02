#ifndef TRANSACTION_PARSER_H
#define TRANSACTION_PARSER_H

#include <QStringList>
#include <QString>
#include <QFile>
#include <QDebug>
#include <QTextStream>
#include <QByteArray>
#include <QList>
#include <QDate>
#include <QChar>

struct Transaction {
    QString date;
    QString reference;
    QString category;
    double  amount;
};


class TransactionParserInterface
{
public:
    TransactionParserInterface();
    virtual ~TransactionParserInterface();

    virtual QList<Transaction> parseTransactions(QFile* file) = 0;
};

class BNPTransactionParser : public TransactionParserInterface
{
public:
    QList<Transaction> parseTransactions(QFile* file) override;

};

#endif // TRANSACTION_PARSER_H
