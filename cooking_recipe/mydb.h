#ifndef MYDB_H
#define MYDB_H
#include <QDebug>

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QFile>
#include <QDebug>
#include <QSqlError>
#include <QSqlQueryModel>


class MyDB
{
// Private means that members are accessible only from within other members of the same class or from their friends
private:
    MyDB();
    // THe following pointer (*instance) is used in mydb.cpp
    static MyDB *instance;
    void init();
    QSqlDatabase db;

// These members that are accessible from anywhere where the object is visible
public:
    static MyDB* getInstance();
    static void ResetInstance();
    QSqlDatabase getDBInstance();
    ~MyDB();
};
#endif // MYDB_H
