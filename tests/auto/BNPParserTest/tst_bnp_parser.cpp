#include <QtTest>

#include "transaction_parser.h"

class BNPParserTest : public QObject
{
    Q_OBJECT

private slots:
    void testTransactionParsing();
    void testParseNegativeAmount();
    void testParseAmountNotNumber();
    void testParseFullDate();
    void testParseDateWrongFormat();
    void testParseCategoryNotExist();
    void testParseCategory();
};

void BNPParserTest::testTransactionParsing()
{
    BNPTransactionParser parser;
    QString transaction_string = "05-08-2019;Téléphone;PRELEVEMENT ORANGE DU 05/08 - MOTIF "
                                 ": VOTRE ABONNEMENT MOBILE: 07XXXXX117 (FACTURE: 2845415892) - "
                                 "REF : 162037106375547865284541589250 LIB;-19.99;";
    Transaction parsed_transaction = parser.parseTransaction(transaction_string);
    QVERIFY(parsed_transaction.date == "2019-08-05");
    QVERIFY(parsed_transaction.reference == "PRELEVEMENT ORANGE DU 05/08 - MOTIF : VOTRE "
                                            "ABONNEMENT MOBILE: 07XXXXX117 (FACTURE: 2845415892) - "
                                            "REF : 162037106375547865284541589250 LIB");
    QVERIFY(parsed_transaction.category == "utilities");
    QCOMPARE(parsed_transaction.amount, -19.99);
}

void BNPParserTest::testParseNegativeAmount()
{
    BNPTransactionParser parser;
    QString amount = "-4,58";
    QVERIFY_EXCEPTION_THROWN(parser.parseAmount(amount), char* const);
}

void BNPParserTest::testParseAmountNotNumber()
{
    BNPTransactionParser parser;
    QString amount = "random";
    QVERIFY_EXCEPTION_THROWN(parser.parseAmount(amount), char* const);
}

void BNPParserTest::testParseFullDate()
{
    BNPTransactionParser parser;
    QString date = "23-09-2018";
    QVERIFY(parser.parseDate(date) == "2018-09-23");
}

void BNPParserTest::testParseDateWrongFormat()
{
    BNPTransactionParser parser;
    QString date = "September 23 2019";
    QVERIFY_EXCEPTION_THROWN(parser.parseDate(date), char* const);
}

void BNPParserTest::testParseCategory()
{
    BNPTransactionParser parser;
    QString category = "Salaires et revenus d'activité";
    QVERIFY(parser.parseCategory(category) == "income");
}

void BNPParserTest::testParseCategoryNotExist()
{
    BNPTransactionParser parser;
    QString category = "Salaires et renus d'activité";
    QVERIFY_EXCEPTION_THROWN(parser.parseCategory(category), char* const);
}
QTEST_MAIN(BNPParserTest)

#include "tst_bnp_parser.moc"
