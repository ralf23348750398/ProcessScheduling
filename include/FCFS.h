#pragma once

#include "schedulingStrategy.h"

class FCFS: public schedulingStrategy{
private:
void sortProcesses() override;

public:
FCFS(std::vector<std::shared_ptr<Process>> proc, bool preemptive);

};