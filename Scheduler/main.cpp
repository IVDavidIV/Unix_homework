#include "scheduler.hpp"

int main() {
    JobScheduler scheduler;

    scheduler.submitBatch({
        Process(101, 5),
        Process(102, 2),
        Process(103, 8),
        Process(104, 3)
    });

    scheduler.runSJF();

    return 0;
}
