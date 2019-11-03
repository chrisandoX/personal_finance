#ifndef DBMANAGER_H
#define DBMANAGER_H

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlRecord>
#include <QDebug>
#define SQL(...) #__VA_ARGS__

/**
 * \class DbManager
 *
 * \brief SQL Database Manager class
 *
 * DbManager sets up the connection with SQL database
 * and performs some basics queries. The class requires
 * existing SQL database. You can create it with sqlite:
 * 1. $ sqlite3 phinance.db
 * 2. sqilte> CREATE TABLE "transactions" (
    "id"	INTEGER PRIMARY KEY AUTOINCREMENT,
    "date"	TEXT,
    "title"	TEXT,
    "amount"	INTEGER,
    "category"	TEXT,
    UNIQUE("date","title","amount","category"));
 * 3. sqlite> .quit
 */
class DbManager
{
public:
    /**
     * @brief Constructor
     *
     * Constructor sets up connection with db and opens it
     * @param path - absolute path to db file
     */
    DbManager(const QString& path);

    /**
     * @brief Destructor
     *
     * Close the db connection
     */
    ~DbManager();

    bool isOpen() const;

    /**
     * @brief Creates a new 'transaction' table if it doesn't already exist
     * @return true - 'transaction' table created successfully, false - table not created
     */
    bool createTable();

private:
    QSqlDatabase m_db;
};

#endif // DBMANAGER_H
