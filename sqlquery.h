#ifndef SQLQUERY_H
#define SQLQUERY_H

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QVariant>

class sqlQuery
{
public:
    static sqlQuery* Instance(QString filename);
    void createTable(QString tablename);
    void insertTable(QString tablename,QString username,int score);
    void updataTable(QString tablename,QString username,int score);
    void delData(QString &sql);
    QString select(QString tablename,QString username);

private:
    sqlQuery(QString &filename);
    ~sqlQuery();
    static sqlQuery* sqlIns;
    static QSqlDatabase db;
};

#endif // SQLQUERY_H
