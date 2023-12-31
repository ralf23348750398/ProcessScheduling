#pragma once

#include <vector>
#include <memory>

#include "CustomProcess.h"

class schedulingStrategy{
private:
    virtual void sortProcesses()=0;

protected:
    std::vector<std::shared_ptr<Process>> processes;
    bool preemptive;
    virtual double getAvgResponseTimeNonPmt() const;    //non-preemptive version
    double getAvgResponseTimePmt();                     //preemptive version

public:
    schedulingStrategy(std::vector<std::shared_ptr<Process>> proc);
    virtual double getAvgResponseTime();
    std::vector<std::shared_ptr<Process>> getProcesses() const;
};