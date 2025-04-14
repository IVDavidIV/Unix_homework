#include "scheduler.hpp"
#include <iostream>

int main() {
    JobScheduler scheduler;

    std::cout << "==== Shortest Job First (SJF) Scheduler ====" << std::endl;

    char choice;
    do {
        pid_t pid;
        size_t burst;

        std::cout << "\nEnter Process ID (PID): ";
        std::cin >> pid;

        std::cout << "Enter Burst Time: ";
        std::cin >> burst;

        scheduler.submitProcess(Process(pid, burst));

        std::cout << "Add another process? (y/n): ";
        std::cin >> choice;

    } while (choice == 'y' || choice == 'Y');

    scheduler.runSJF();

    return 0;
}
