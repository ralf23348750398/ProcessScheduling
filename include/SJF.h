#pragma once

#include "schedulingStrategy.h"

class SJF: public schedulingStrategy{
private:
void sortProcesses() override;



public:
SJF(std::vector<std::shared_ptr<Process>> proc, bool preemtive);

};