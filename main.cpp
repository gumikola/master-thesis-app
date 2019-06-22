#include <brute_force/brute_force.h>
#include <simulated_annealing/simulated_annealing.h>
#include <tasks/tasks.h>

int main()
{
    JobStruct a = JobStruct("1", *new QVector<uint>({1, 1, 1, 1, 1}), *new QVector<uint>({10, 15}));
    JobStruct b = JobStruct("2", *new QVector<uint>({1, 1, 1, 1, 1}), *new QVector<uint>({9, 18}));

    TasksClass test;

    test.add_task(a);
    test.add_task(b);

    test = simulated_annealing(test, 380, 30, 0.4);
    test.print();

    return 0;
}
