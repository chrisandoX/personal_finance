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
       return date_parsed;
    }

    qdate = QDate::fromString(date, "yyyy MMMM d");
    if(qdate.isValid())
    {
       date_parsed = qdate.toString(Qt::ISODate);
       return date_parsed;
    }
    else
        throw "Date does fit yyyy MMMM d format";
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

double RevoluteTransactionParser::parseAmount(QString paid_in_string, QString paid_out_string)
{
    double amount_parsed;

    bool to_double_ok;
    double paid_out = paid_out_string.replace(",", ".").toDouble(&to_double_ok);
    if(!(to_double_ok || paid_out_string == ""))
        throw "Paid out is not a number";

    double paid_in = paid_in_string.replace(",", ".").toDouble(&to_double_ok);
    if(!(to_double_ok || paid_in_string == ""))
        throw "Paid in is not a number";

    if(paid_out < 0)
        throw "Paid out amount cannot be negative";

    if(paid_in < 0)
        throw "Paid in amount cannot be negative";

    if(paid_in_string == "")
    {
        //TODO automatically detect wheter . or ,
        amount_parsed = paid_out*(-1.0);
    }
    else if (paid_out_string == "")
    {
        amount_parsed = paid_in;
    }
    else
        throw "Invalid amount entry";
    return amount_parsed;
}

BNPTransactionParser::BNPTransactionParser()
{
    QMapIterator<QString, QString> i(bnp_category_map);
    while (i.hasNext()) {
        i.next();
        bnp_category_map_normalized.insert(
            i.key().normalized(QString::NormalizationForm_KD),
            i.value());
    }
}


Transaction BNPTransactionParser::parseTransaction(QString transaction_string)
{
    QStringList lineToken = transaction_string.split(";");
    Transaction transaction;

    transaction.date = this->parseDate(lineToken.at(0));
    transaction.reference = this->parseReference(lineToken.at(2));
    transaction.category = this->parseCategory(lineToken.at(1));
    transaction.amount = this->parseAmount(lineToken.at(3));
    return transaction;
}

QList<Transaction> BNPTransactionParser::parseTransactionList(QFile *file)
{
    QTextStream in(file);
    QList<Transaction> transactionsList;

    // Read first line 3 times and do nothing to get rid of header
    for(int i = 0; i<3; i++)
        in.readLine();

    while(!in.atEnd())
    {
        QString fileLine = in.readLine();
        Transaction transaction = this->parseTransaction(fileLine);
        transactionsList.append(transaction);
    }

    return transactionsList;
}

QString BNPTransactionParser::parseDate(QString date)
{
    QString date_parsed;
    QDate qdate = QDate::fromString(date, "dd-MM-yyyy");
    if(qdate.isValid())
    {
       date_parsed = qdate.toString(Qt::ISODate);
       return date_parsed;
    }
    else
        throw "Date does fit dd-MM-yyyy format";
}

QString BNPTransactionParser::parseCategory(QString category)
{
    QString category_normalized = category.normalized(QString::NormalizationForm_KD);
    if(!bnp_category_map_normalized.contains(category_normalized)){
        qDebug() << "Category " << category <<" does not exists";
        throw "Category does not exist";
    }
    else
        return bnp_category_map_normalized[category_normalized];
}

QString BNPTransactionParser::parseReference(QString reference)
{
    return reference;
}

double BNPTransactionParser::parseAmount(QString amount)
{
    bool to_double_ok;
    double amount_parsed = amount.toDouble(&to_double_ok);
    if(!to_double_ok)
         throw "Amount in is not a number";
    return amount_parsed;
}

double BNPTransactionParser::parseAmount(QString amount_0, QString amount_1)
{
    return 0;
}
