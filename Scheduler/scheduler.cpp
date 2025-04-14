#include "scheduler.hpp"

JobScheduler::JobScheduler() {}

JobScheduler::~JobScheduler() {
    _jobList.clear();
}

void JobScheduler::submitProcess(const Process& p) {
    _jobList.push_back(p);
}

void JobScheduler::submitBatch(const std::vector<Process>& batch) {
    for (const auto& p : batch) {
        _jobList.push_back(p);
    }
}

std::vector<Process> JobScheduler::getScheduledJobs() const {
    return _jobList;
}

void JobScheduler::runSJF() {
    std::sort(_jobList.begin(), _jobList.end(), [](const Process& a, const Process& b) {
        return a.burstTime < b.burstTime;
    });

    int currentTime = 0;

    for (auto& job : _jobList) {
        job.waitingTime = currentTime;
        currentTime += job.burstTime;
        job.completionTime = currentTime;
        job.turnaroundTime = job.completionTime; 
    }

    std::cout << "\n=== SJF Scheduling Results ===\n";
    std::cout << "PID\tBurst\tWaiting\tTurnaround\tCompletion\n";
    for (const auto& job : _jobList) {
        std::cout << job.pid << "\t"
                  << job.burstTime << "\t"
                  << job.waitingTime << "\t"
                  << job.turnaroundTime << "\t\t"
                  << job.completionTime << "\n";
    }
}
