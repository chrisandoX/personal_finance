#include <QtTest>

#include "transaction_parser.h"

class RevoluteParserTest : public QObject
{
    Q_OBJECT

private slots:
    void testTransactionParsing();
    void testParseNegativeAmount();
    void testParseAmountNotNumber();
    void testParsePartialDate();
    void testParseFullDate();
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
    QString paid_in = "-4,58";
    QString paid_out = "-2,0";
    QVERIFY_EXCEPTION_THROWN(parser.parseAmount(paid_in, ""), char* const);
    QVERIFY_EXCEPTION_THROWN(parser.parseAmount("", paid_out), char* const);
}

void RevoluteParserTest::testParseAmountNotNumber()
{
    RevoluteTransactionParser parser;
    QString paid_in = "random";
    QString paid_out = "number";
    QVERIFY_EXCEPTION_THROWN(parser.parseAmount(paid_in, ""), char* const);
    QVERIFY_EXCEPTION_THROWN(parser.parseAmount("", paid_out), char* const);
}

void RevoluteParserTest::testParsePartialDate()
{
    RevoluteTransactionParser parser;
    QString date = "September 23";
    int current_year = QDate().currentDate().year();
    QString test_year = QString::number(current_year)+"-"+"09-23";
    QVERIFY(parser.parseDate(date) == test_year);
}

void RevoluteParserTest::testParseFullDate()
{
    RevoluteTransactionParser parser;
    QString date = "2018 September 23";
    QVERIFY(parser.parseDate(date) == "2018-09-23");
}
QTEST_MAIN(RevoluteParserTest)

#include "tst_revolute_parser.moc"
