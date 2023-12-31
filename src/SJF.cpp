#include "SJF.h"
#include "schedulingStrategy.h"
#include "Process.h"

#include <algorithm>

SJF::SJF(std::vector<std::shared_ptr<Process>> proc, bool preemptive) : schedulingStrategy(proc){
    this->preemptive = preemptive;
    sortProcesses();
}

void SJF::sortProcesses() {
    std::sort(processes.begin(), processes.end(),
              [](const std::shared_ptr<Process>& a, const std::shared_ptr<Process>& b) {
                  return a->getExecutionTime() < b->getExecutionTime();
              });
}



