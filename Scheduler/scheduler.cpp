#include "scheduler.hpp"

JobScheduler::JobScheduler() {}

JobScheduler::~JobScheduler() {}

void JobScheduler::submitProcess(const Process& p) {
    _jobQueue.push(p);
}

void JobScheduler::runSJF() {
    int currentTime = 0;

    std::vector<Process> finishedJobs;

    while (!_jobQueue.empty()) {
        Process current = _jobQueue.top();
        _jobQueue.pop();

        current.waitingTime = currentTime;
        currentTime += current.burstTime;
        current.completionTime = currentTime;
        current.turnaroundTime = current.completionTime;

        finishedJobs.push_back(current);
    }

    std::cout << "\n=== SJF Scheduling Results (Using Priority Queue) ===\n";
    std::cout << "PID\tBurst\tWaiting\tTurnaround\tCompletion\n";

    for (const auto& job : finishedJobs) {
        std::cout << job.pid << "\t"
                  << job.burstTime << "\t"
                  << job.waitingTime << "\t"
                  << job.turnaroundTime << "\t\t"
                  << job.completionTime << "\n";
    }
}
