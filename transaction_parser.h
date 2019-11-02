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
    virtual QString parseDate(QString date) = 0;
    virtual QString parseReference(QString reference) = 0;
    virtual QString parseCategory(QString category) = 0;
    virtual double parseAmount(QString amount) = 0;
    virtual double parseAmount(QString amount_0, QString amount_1) = 0;
};

class BNPTransactionParser : public TransactionParserInterface
{
public:
    QList<Transaction> parseTransactions(QFile* file) override;
    QString parseDate(QString date) override;
    QString parseCategory(QString category) override;
    QString parseReference(QString reference) override;
    double parseAmount(QString amount) override;
    double parseAmount(QString paid_in, QString paid_out) override;

};

#endif // TRANSACTION_PARSER_H
