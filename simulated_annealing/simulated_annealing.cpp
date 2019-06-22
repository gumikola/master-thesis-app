#include "simulated_annealing.h"
#include <algorithm>
#include <QDateTime>
#include <QRandomGenerator>

TasksClass swap_rand(TasksClass source, QRandomGenerator& rand)
{

    std::swap(source[rand.bounded(source.size())], source[rand.bounded(source.size())]);

    return source;
}

TasksClass simulated_annealing(TasksClass task, double temp_start, double temp_stop, double lambda)
{
    quint32          seed = static_cast<quint32>(QDateTime::currentSecsSinceEpoch());
    QRandomGenerator rand(seed);

    TasksClass best = task;

    double temp = temp_start;

    while (temp > temp_stop)
    {
        TasksClass new_task = swap_rand(task, rand);

        double delta = (new_task.calc_makespan() - task.calc_makespan());

        if (best.calc_makespan() > new_task.calc_makespan())
        {
            best = new_task;
        }
        if (delta <= 0)
        {
            task = new_task;
        }
        else
        {
            double p = exp(-delta / temp);
            if (rand.generateDouble() < p)
            {
                task = new_task;
            }
        }

        temp *= lambda;
    }
    return best;
}
