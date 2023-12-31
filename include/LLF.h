#pragma once

#include "schedulingStrategy.h"

class LLF: public schedulingStrategy{
private:
void sortProcesses() override;

public:
LLF(std::vector<std::shared_ptr<Process>> proc, bool preemptive);

};