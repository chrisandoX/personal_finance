#include <QtTest>

#include "dbmanager.h"

class DbManagerTest : public QObject
{
    Q_OBJECT

private slots:
    void testDbConnection();
    void testCreateTable();
    void testAddTransaction();
};

void DbManagerTest::testDbConnection()
{
    QString database_path = "";
    DbManager db(database_path);
    QVERIFY(db.isOpen() == true);
}

void DbManagerTest::testCreateTable()
{
    QString database_path = "";
    DbManager db(database_path);
    QVERIFY(db.createTable() == true);
}

void DbManagerTest::testAddTransaction()
{
    QString database_path = "";
    DbManager db(database_path);
    db.createTable();
    Transaction transaction;
    transaction.date = "2019-10-01";
    transaction.category = "test";
    transaction.reference = "test_reference";
    transaction.amount = 999;
    QVERIFY(db.addTransaction(transaction) == true);

    QSqlQuery query("SELECT * FROM transactions");
    while (query.next())
    {
        QCOMPARE(query.value(1), transaction.date);
        QCOMPARE(query.value(2), transaction.reference);
        QCOMPARE(query.value(3), transaction.amount);
        QCOMPARE(query.value(4), transaction.category);
    }

}

QTEST_MAIN(DbManagerTest)

#include "tst_dbmanager.moc"
