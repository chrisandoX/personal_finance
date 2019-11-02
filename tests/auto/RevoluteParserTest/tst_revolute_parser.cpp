#include <QtTest>

#include "transaction_parser.h"

class RevoluteParserTest : public QObject
{
    Q_OBJECT

private slots:
    void testTransactionParsing();
    void testParseNegativeAmount();

};

void RevoluteParserTest::testTransactionParsing()
{
    RevoluteTransactionParser parser;
    QString transaction_string = "October 19;IKEA;4,58;;CHF 5,00;;12,24;restaurants";
    Transaction parsed_transaction = parser.parseTransaction(transaction_string);
    QVERIFY(parsed_transaction.date == "2019-10-19");
    QVERIFY(parsed_transaction.reference == "IKEA");
    QVERIFY(parsed_transaction.category == "restaurants");
    QCOMPARE(parsed_transaction.amount, -4.58);
}

void RevoluteParserTest::testParseNegativeAmount()
{
    RevoluteTransactionParser parser;
    QString amount_string = "-4,58";
    double amount_parsed = parser.parseAmount(amount_string);
    QCOMPARE(amount_parsed, 4.58);
}

QTEST_MAIN(RevoluteParserTest)

#include "tst_revolute_parser.moc"
