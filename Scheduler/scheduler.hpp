#ifndef SCHEDULER_HPP
#define SCHEDULER_HPP

#include <iostream>
#include <queue>
#include <vector>

struct Process {
    size_t burstTime;
    pid_t pid;

    int completionTime = 0;
    int turnaroundTime = 0;
    int waitingTime = 0;

    Process(pid_t id, size_t bt) : burstTime(bt), pid(id) {}
};

// Custom comparator for priority_queue (min-heap by burstTime)
struct CompareBurst {
    bool operator()(const Process& a, const Process& b) {
        return a.burstTime > b.burstTime;  // smaller burstTime = higher priority
    }
};

class JobScheduler {
public:
    JobScheduler();
    ~JobScheduler();

    void runSJF();
    void submitProcess(const Process& p);

private:
    std::priority_queue<Process, std::vector<Process>, CompareBurst> _jobQueue;
};

#endif // SCHEDULER_HPP
