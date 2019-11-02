#include "transaction_parser.h"

TransactionParserInterface::TransactionParserInterface()
{

}

TransactionParserInterface::~TransactionParserInterface()
{

}

Transaction RevoluteTransactionParser::parseTransaction(QString transaction_string)
{
    QStringList lineToken = transaction_string.split(";");
    Transaction transaction;

    transaction.date = this->parseDate(lineToken.at(0));
    transaction.reference = this->parseReference(lineToken.at(1));
    transaction.category = this->parseCategory(lineToken.at(7));
    transaction.amount = this->parseAmount(lineToken.at(3), lineToken.at(2));
    return transaction;
}

QList<Transaction> RevoluteTransactionParser::parseTransactionList(QFile* file)
{
    QTextStream in(file);
    QList<Transaction> transactionsList;

    // Read first line and do nothing to get rid of header
    in.readLine();

    while(!in.atEnd())
    {
        QString fileLine = in.readLine();
        Transaction transaction = this->parseTransaction(fileLine);
        transactionsList.append(transaction);
    }

    return transactionsList;
}

QString RevoluteTransactionParser::parseDate(QString date)
{
    QString date_parsed;
    QDate qdate = QDate::fromString(date, "MMMM d");
    if(qdate.isValid())
    {
       // Replace default year to current year
       int current_year = QDate().currentDate().year();
       qdate.setDate(current_year, qdate.month(), qdate.day());
       date_parsed = qdate.toString(Qt::ISODate);
    }
    else
    {
       date_parsed = QDate::fromString(date, "yyyy MMMM d").toString(Qt::ISODate);
    }
    return date_parsed;
}

QString RevoluteTransactionParser::parseCategory(QString category)
{
    QString category_parsed;
    category_parsed = category.remove(QChar(','), Qt::CaseInsensitive);
    return category_parsed;
}

QString RevoluteTransactionParser::parseReference(QString reference)
{
    //TODO fix encoding
    return reference;
}
double RevoluteTransactionParser::parseAmount(QString amount)
{
    return amount.toDouble();
}

double RevoluteTransactionParser::parseAmount(QString paid_in, QString paid_out)
{
    double amount_parsed;

    if(paid_in == "")
    {
        //TODO automatically detect wheter . or ,
        amount_parsed = paid_out.replace(",", ".").toDouble()*(-1.0);
    }
    else if (paid_out == "")
    {
        amount_parsed = paid_in.replace(",", ".").toDouble();
    }
    else{
        amount_parsed = 0;
        qDebug() << "Transaction has no value";
    }
    return amount_parsed;
}

