#pragma once

#include <vector>
#include <iostream>
#include <mutex>

#include "CustomProcess.h"
#include "schedulingStrategy.h"

class ArgumentHandler{
private:
    std::vector<std::string> processParameters;
    std::string strategy;
    std::vector<std::shared_ptr<Process>> processes;
    int quantum;
    bool preemptive;
    std::mutex resultsMutex;

    void createDefaultProcesses();
    void createProcesses();
    void simulateScheduling();
    void printProcesses(const std::vector<std::shared_ptr<Process>>& proc) const;
    void printResults(std::string strategy, schedulingStrategy& obj);
    void printHelp();

public:
    ArgumentHandler(int argc, char* argv[]);
    void processArguments();
};