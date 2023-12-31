#pragma once

#include <string>

class Process{
private:
    std::string name;
    int readyTime;
    int executionTime;
    int deadline;

public:
    //name, readyTime, executionTime, deadline
    Process(std::string n, int r, int e, int d);

    std::string getName();
    int getReadyTime();
    int getExecutionTime();
    int getDeadline();

    void setReadyTime(int r);
    void setExecutionTime(int e);
};
