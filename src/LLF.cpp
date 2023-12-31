#include "LLF.h"
#include "schedulingStrategy.h"
#include "Process.h"

#include <algorithm>

LLF::LLF(std::vector<std::shared_ptr<Process>> proc, bool preemptive) : schedulingStrategy(proc){
    this->preemptive = preemptive;
    sortProcesses();
}

void LLF::sortProcesses() {
    std::sort(processes.begin(), processes.end(),
              [](const std::shared_ptr<Process>& a, const std::shared_ptr<Process>& b) {
                int laxA = a->getDeadline() - a->getReadyTime() - a->getExecutionTime();
                int laxB = b->getDeadline() - b->getReadyTime() - b->getExecutionTime();
                return laxA < laxB;
              });
}