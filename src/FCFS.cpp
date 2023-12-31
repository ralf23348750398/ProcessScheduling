#include "FCFS.h"
#include "schedulingStrategy.h"
#include "CustomProcess.h"

#include <algorithm>

FCFS::FCFS(std::vector<std::shared_ptr<Process>> proc, bool preemptive) : schedulingStrategy(proc){
    this->preemptive = preemptive;
    sortProcesses();
}

void FCFS::sortProcesses() {}