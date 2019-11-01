#ifndef TRANSACTION_PARSER_H
#define TRANSACTION_PARSER_H

#include <QStringList>
#include <QString>
#include <QFile>
#include <QDebug>
#include <QTextStream>

class TransactionParserInterface
{
public:
    TransactionParserInterface();
    virtual ~TransactionParserInterface();

    virtual QStringList parseTransactions(QFile* file) = 0;
};

class BNPTransactionParser : public TransactionParserInterface
{
public:
    QStringList parseTransactions(QFile* file) override;

};

#endif // TRANSACTION_PARSER_H
