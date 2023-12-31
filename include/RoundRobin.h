#pragma once

#include "schedulingStrategy.h"

class RoundRobin: public schedulingStrategy{
private:
    void sortProcesses() override;
    int quantum;

public:
    RoundRobin(std::vector<std::shared_ptr<Process>> proc, int q);
    double getAvgResponseTime() override;

};