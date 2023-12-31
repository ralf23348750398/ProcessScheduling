#include "CustomProcess.h"

Process::Process(std::string n, int r, int e, int d){
    name=n;
    readyTime=r;
    executionTime=e;
    deadline=d;
}

std::string Process::getName(){
    return name;
}

int Process::getReadyTime(){
    return readyTime;
}

int Process::getExecutionTime(){
    return executionTime;
}

int Process::getDeadline(){
    return deadline;
}

void Process::setReadyTime(int r){
    readyTime = r;
}

void Process::setExecutionTime(int e){
    executionTime = e;
}