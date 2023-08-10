#include "dbconnection.h"

DbConnection::DbConnection()
{

    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("../MedicalData/INTFETAL.sqlite");
}

QSqlError DbConnection::openDB()
{

    if( !db.open() ){
        return db.lastError().text();
    }

    else{
        return QSqlError();
    }
}
