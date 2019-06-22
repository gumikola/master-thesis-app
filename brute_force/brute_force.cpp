#include "brute_force.h"

TasksClass brute_force(TasksClass task)
{
    TasksClass best          = TasksClass();
    uint       best_makespan = UINT_MAX;

    do
    {
        if (task.calc_makespan() < best_makespan)
        {
            best = task;
        }
    } while (std::next_permutation(task.begin(), task.end()));

    return best;
}
