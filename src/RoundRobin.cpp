#include "RoundRobin.h"
#include "schedulingStrategy.h"
#include "Process.h"

#include <algorithm>

RoundRobin::RoundRobin(std::vector<std::shared_ptr<Process>> proc, int q) : schedulingStrategy(proc){
    quantum = q;
    sortProcesses();
}

void RoundRobin::sortProcesses() {}

double RoundRobin::getAvgResponseTime(){
    int responseTime = 0, currentTime = 0;
    int nrProcesses = processes.size();

    while([&]() -> bool {
            int totalExecutionTime = 0;

            for(const auto& i : processes){
                totalExecutionTime += i->getExecutionTime();}
        
            return totalExecutionTime > 0;}()){
        
        bool noProcessReady=1;
        for(const auto& i : processes){
            if(i->getReadyTime()<=currentTime && i->getExecutionTime()>0){
                noProcessReady = 0;
                if((i->getExecutionTime() - quantum) > 0){
                    currentTime += quantum;
                    i->setExecutionTime(i->getExecutionTime() - quantum);

                    //std::cout << i->getName() << "(" << quantum << ") | ";
                }
                else if ((i->getExecutionTime() - quantum) <= 0){
                    currentTime += i->getExecutionTime();

                    //std::cout << i->getName() << "(" << i->getExecutionTime() << ") | ";

                    i->setExecutionTime(0);
                    responseTime += currentTime;
                }
            }
        }
        if(noProcessReady){
            currentTime += quantum; //stall
            //std::cout << "2 | ";
        }
    }
    //std::cout << std::endl;

    return static_cast<double>(responseTime)/nrProcesses;
}