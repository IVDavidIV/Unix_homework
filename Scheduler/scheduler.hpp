#ifndef SCHEDULER_HPP
#define SCHEDULER_HPP

#include <iostream>
#include <vector>
#include <algorithm>

struct Process {
    size_t burstTime;
    int remainingTime;
    pid_t pid;

    int completionTime = 0;
    int turnaroundTime = 0;
    int waitingTime = 0;

    Process(pid_t id, size_t bt) : pid(id), burstTime(bt), remainingTime(bt) {}
};

class JobScheduler {
public:
    JobScheduler();
    ~JobScheduler();

    void runSJF();
    void submitProcess(const Process& p);
    void submitBatch(const std::vector<Process>& batch);
    std::vector<Process> getScheduledJobs() const;

private:
    std::vector<Process> _jobList;
};

#endif // SCHEDULER_HPP
