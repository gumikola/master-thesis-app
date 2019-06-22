#ifndef DATABASE_H
#define DATABASE_H

#include <QtSql/QtSql>
#include <tasks/tasks.h>

class Database
{
    const QString driver_name = "QSQLITE";
    const QString path_to_db  = "/home/mguz/workspace/app_cpp/db.sqlite";

    QSqlDatabase  driver;
    QVector<uint> opertion_time(int id);
    QVector<uint> changeover_time(int id);

public:
    Database();
    ~Database();
    TasksClass fetch_by_id(int id, int quantity);
};

#endif // DATABASE_H
