#include <dbmanager.h>


DbManager::DbManager(const QString &path)
{
    m_db = QSqlDatabase::addDatabase("QSQLITE");
    m_db.setDatabaseName(path);

    if (!m_db.open())
    {
        qDebug() << "Error: connection with database fail";
    }
    else
    {
        qDebug() << "Database: connection ok";
    }
}

DbManager::~DbManager()
{
    if (m_db.isOpen())
    {
        m_db.close();
    }
}

bool DbManager::isOpen() const
{
    return m_db.isOpen();
}

bool DbManager::createTable()
{
    bool success = false;

    QSqlQuery query;
    query.prepare(SQL(CREATE TABLE transactions (
                      id	INTEGER PRIMARY KEY AUTOINCREMENT,
                      date       TEXT,
                      title      TEXT,
                      amount     INTEGER,
                      category   TEXT,
                      UNIQUE("date","title","amount","category"))));

    if (!query.exec())
    {
        qDebug() << "Couldn't create the table 'transctions': one might already exist.";
        success = false;
    }
    else
    {
        success = true;
        qDebug() << "Database Created";
    }

    return success;
}

bool DbManager::addTransaction(Transaction transaction)
{
    bool success = false;

    QSqlQuery query;
    query.prepare("INSERT INTO transactions(date, title, amount, category) "
                   "VALUES (:date, :title, :amount, :category)");
    query.bindValue(":date", transaction.date);
    query.bindValue(":title", transaction.reference);
    query.bindValue(":amount", transaction.amount);
    query.bindValue(":category", transaction.category);

    if(!query.exec())
    {
        qDebug()<<query.lastError();
        success = false;
    }
    else
    {
        success = true;
        qDebug() << transaction.date
                 << transaction.reference
                 << transaction.amount
                 << transaction.category;
    }
    return success;
}


