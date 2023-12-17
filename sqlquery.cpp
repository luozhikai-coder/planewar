#include "sqlquery.h"


sqlQuery* sqlQuery::sqlIns = NULL;
QSqlDatabase sqlQuery::db;
sqlQuery::sqlQuery(QString &filename)
{

    //�ж����ݿ��Ƿ�������
    if(QSqlDatabase::contains("qt_sql_default_connection"))
        db = QSqlDatabase::database("qt_sql_default_connection");
    else
        db = QSqlDatabase::addDatabase("QSQLITE");
    //�������ݿ�����
    db.setDatabaseName(filename);
    if(!db.open())
        qDebug()<<":::::::Failed to open database!:::::::"<<db.lastError();
    else
        qDebug()<<":::::::Open database!:::::::";
}

//��ȡ���ݿ����ʵ��
sqlQuery* sqlQuery::Instance(QString filename)
{
    if(!sqlIns)
        sqlIns = new sqlQuery(filename);
    return sqlIns;
}
//�������ݿ��
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
//���ݲ������ݿ�
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
//�������ݿ�����
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
//��ѯ���ݿ�����
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
