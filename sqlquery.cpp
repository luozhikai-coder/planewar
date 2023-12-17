#include "sqlquery.h"


sqlQuery* sqlQuery::sqlIns = NULL;
QSqlDatabase sqlQuery::db;
sqlQuery::sqlQuery(QString &filename)
{

    //判断数据库是否已连接
    if(QSqlDatabase::contains("qt_sql_default_connection"))
        db = QSqlDatabase::database("qt_sql_default_connection");
    else
        db = QSqlDatabase::addDatabase("QSQLITE");
    //设置数据库名称
    db.setDatabaseName(filename);
    if(!db.open())
        qDebug()<<":::::::Failed to open database!:::::::"<<db.lastError();
    else
        qDebug()<<":::::::Open database!:::::::";
}

//获取数据库对象实例
sqlQuery* sqlQuery::Instance(QString filename)
{
    if(!sqlIns)
        sqlIns = new sqlQuery(filename);
    return sqlIns;
}
//创建数据库表
void sqlQuery::createTable(QString tablename)
{
    QSqlQuery sqlQuery(db);
    QString sql = QString("create table %1(username varchar(20) primary key,score int);").arg(tablename);
    if(!sqlQuery.exec(sql))
    {
        qDebug()<<"Failed to create table:"<<sqlQuery.lastError();
    }
    else
    {
        qDebug()<<"success to create table";
    }
}
//数据插入数据库
void sqlQuery::insertTable(QString tablename,QString username,int score)
{
    QSqlQuery sqlQuery(db);
    QString sql = QString("insert into %1 values('%2',%3)").arg(tablename).arg(username).arg(score);
    if(!sqlQuery.exec(sql))
    {
        qDebug()<<"Failed to insert table:"<<sqlQuery.lastError();
    }
    else
    {
        qDebug()<<"success to insert table";
    }

}
//更新数据库数据
void sqlQuery::updataTable(QString tablename,QString username,int score)
{
    QSqlQuery sqlQuery(db);
    QString sql = QString("update %1 set score = %2 where username = '%3' and score < %4").arg(tablename).arg(score).arg(username).arg(score);
    if(!sqlQuery.exec(sql))
    {
        qDebug()<<"Failed to update table:"<<sqlQuery.lastError();
    }
    else
    {
        qDebug()<<"success to update table";
    }
}
void sqlQuery::delData(QString &sql)
{

}
//查询数据库数据
QString sqlQuery::select(QString tablename,QString username)
{
    QSqlQuery sqlQuery(db);
    QString sql = QString("select *from %1").arg(tablename);
    if(!sqlQuery.exec(sql))
    {
        qDebug()<<"Failed to select table:"<<sqlQuery.lastError();
    }
    else
    {
        while(sqlQuery.next())
        {
            if(sqlQuery.value(0).toString() == username)
            {
                return sqlQuery.value(1).toString();
            }
        }
    }
    return NULL;

}
