#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QTableView>
#include <QSqlError>
#include <QFileDialog>
#include <QMessageBox>
#include "transaction_parser.h"
#include "dbmanager.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    DbManager db;

private slots:
    void on_pushButton_clicked();

    void on_dateFrom_userDateChanged(const QDate &date);

    void on_dateUntil_userDateChanged(const QDate &date);

    void on_pushButtonShowSelectedTransactions_clicked();

private:
    Ui::MainWindow *ui;

    QDate date_from;
    QDate date_until;
    QSqlTableModel *tableModel;
};
#endif // MAINWINDOW_H
