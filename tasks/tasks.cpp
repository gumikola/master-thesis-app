#include "tasks.h"

TasksClass::TasksClass() {}

uint TasksClass::operation_time(uint idx_machine, uint idx_task)
{
    return this->task[static_cast<int>(idx_task)].p[static_cast<int>(idx_machine)];
}

uint TasksClass::adapt_time(uint idx_machine, uint idx_task)
{
    return this->task[static_cast<int>(idx_task)].s[static_cast<int>(idx_machine)];
}

uint TasksClass::start_operation(uint idx_machine, uint idx_task)
{
    uint condition1 = 0, condition2 = 0;
    if (idx_machine == 0)
    {
        condition1 = 0;
    }
    else
    {
        condition1 = stop_operation(idx_machine - 1, idx_task);
    }

    if (idx_task == 0)
    {
        condition2 = 0;
    }
    else
    {
        condition2 = stop_operation(idx_machine, idx_task - 1) + adapt_time(idx_machine, idx_task);
    }

    return qMax(condition1, condition2);
}

uint TasksClass::stop_operation(uint idx_machine, uint idx_task)
{
    return start_operation(idx_machine, idx_task) + operation_time(idx_machine, idx_task);
}

void TasksClass::add_task(JobStruct job)
{

    job.id = static_cast<uint>(this->task.size());

    this->task.append(job);
}

uint TasksClass::calc_makespan(void)
{
    uint last_machine = static_cast<uint>(this->task.last().p.size() - 1);
    uint last_task    = static_cast<uint>(this->task.size() - 1);
    return stop_operation(last_machine, last_task);
}

int TasksClass::size(void)
{
    return this->task.size();
}
JobStruct& TasksClass::operator[](int idx)
{
    return this->task[idx];
}
QList<JobStruct>::iterator TasksClass::begin(void)
{
    return this->task.begin();
}
QList<JobStruct>::iterator TasksClass::end(void)
{
    return this->task.end();
}

void TasksClass::print(void)
{
    QList<uint> tmp;
    for (auto i : this->task)
    {
        tmp.append(i.id);
    }
    qDebug() << tmp;
}
