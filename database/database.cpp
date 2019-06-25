#include "database.h"

Database::Database()
{
    driver = QSqlDatabase::addDatabase(driver_name);

    driver.setDatabaseName(path_to_db);

    if (driver.open() == false)
    {
        qDebug() << "Can't connect to database";
    }
}

Database::~Database()
{
    driver.close();
}

QVector<uint> Database::opertion_time(int id)
{
    QVector<uint> data;

    QSqlQuery q;

    q.prepare("SELECT * FROM operation_time WHERE id=?");
    q.bindValue(0, id);

    if (q.exec())
    {
        while (q.next())
        {
            data.append(q.value("stencil_printer").toUInt());
            data.append(q.value("pick_and_place").toUInt());
            data.append(q.value("manual_placing").toUInt());
            data.append(q.value("reflow").toUInt());
            data.append(q.value("manual_solder").toUInt());
            data.append(q.value("assembly_check").toUInt());
        }
    }
    else
    {
        qDebug() << q.lastError();
        throw q.lastError().text();
    }

    return data;
}

QVector<uint> Database::changeover_time(int id)
{
    QVector<uint> data;

    QSqlQuery q;

    q.prepare("SELECT * FROM changeover_time WHERE id=?");
    q.bindValue(0, id);

    if (q.exec())
    {
        while (q.next())
        {
            data.append(q.value("stencil_printer").toUInt());
            data.append(q.value("pick_and_place").toUInt());
        }
    }
    else
    {
        qDebug() << q.lastError();
        throw q.lastError().text();
    }

    return data;
}

TasksClass Database::fetch_by_id(int id, int quantity)
{
    TasksClass data;

    QSqlQuery q;

    q.prepare("SELECT * FROM projects WHERE id=?");
    q.bindValue(0, id);

    if (q.exec())
    {
        while (q.next())
        {
            JobStruct side_a, side_b;
            if (q.value("two_side") == true)
            {
                side_a = JobStruct(
                    QString("%1 %2 [Strona A]").arg(q.value("company").toString(), q.value("name").toString()),
                    opertion_time(q.value("operation_side_a").toInt()),
                    changeover_time(q.value("changeover_side_a").toInt()));

                side_b = JobStruct(
                    QString("%1 %2 [Strona B]").arg(q.value("company").toString(), q.value("name").toString()),
                    opertion_time(q.value("operation_side_b").toInt()),
                    changeover_time(q.value("changeover_side_b").toInt()));
            }
            else
            {
                side_a = JobStruct(QString("%1 %2").arg(q.value("company").toString(), q.value("name").toString()),
                                   opertion_time(q.value("operation_side_a").toInt()),
                                   changeover_time(q.value("changeover_side_a").toInt()));
            }

            for (int i = 0; i < quantity; i++)
            {
                data.add_task(side_a);
                if (q.value("two_side") == true)
                {
                    data.add_task(side_b);
                }
            }
        }
    }
    else
    {
        qDebug() << q.lastError();
        throw q.lastError().text();
    }

    return data;
}
