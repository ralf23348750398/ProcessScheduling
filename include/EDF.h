#pragma once

#include "schedulingStrategy.h"

class EDF: public schedulingStrategy{
private:
void sortProcesses() override;

public:
EDF(std::vector<std::shared_ptr<Process>> proc, bool preemptive);

};