#ifndef DBCONNECTION_H
#define DBCONNECTION_H

#include <QtSql>
#include <QSqlDatabase>
class DbConnection
{
public:
    DbConnection();
    QSqlDatabase db;
    QSqlError openDB();

};

#endif // DBCONNECTION_H
