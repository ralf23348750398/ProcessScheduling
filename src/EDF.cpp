#include "EDF.h"
#include "schedulingStrategy.h"
#include "Process.h"

#include <algorithm>

EDF::EDF(std::vector<std::shared_ptr<Process>> proc, bool preemptive) : schedulingStrategy(proc){
    this->preemptive = preemptive;
    sortProcesses();
}

void EDF::sortProcesses() {
    std::sort(processes.begin(), processes.end(),
              [](const std::shared_ptr<Process>& a, const std::shared_ptr<Process>& b) {
                  return a->getDeadline() < b->getDeadline();
              });
}