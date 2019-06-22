#ifndef SA_H
#define SA_H

#include <tasks/tasks.h>

TasksClass simulated_annealing(TasksClass task, double temp_start, double temp_stop, double lambda);
#endif // simulated_annealing_H
