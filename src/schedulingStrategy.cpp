#include "schedulingStrategy.h"

schedulingStrategy::schedulingStrategy(std::vector<std::shared_ptr<Process>> proc){
    //creating a copy of all the processes so that you can simulate execution 
    //of processes without modifying the values of the processes of the caller
    for(const auto& p : proc){
        std::shared_ptr<Process> newP = std::make_shared<Process>(*p);
        processes.push_back(newP);
    }
}

std::vector<std::shared_ptr<Process>> schedulingStrategy::getProcesses() const{
    return processes;
}

double schedulingStrategy::getAvgResponseTime(){
    if (preemptive){
        return getAvgResponseTimePmt();
    }
    else{
        return getAvgResponseTimeNonPmt();
    }
}

double schedulingStrategy::getAvgResponseTimeNonPmt() const{
    double responseTime = 0;
    int currentTime = 0;
    int nrProcesses = processes.size();
    bool processSkipped = 0;

    while([&]() -> bool {
            int totalExecutionTime = 0;

            for(const auto& i : processes){
                totalExecutionTime += i->getExecutionTime();}
        
            return totalExecutionTime > 0;}()){
        
        bool noProcessReady=1;
        for(const auto& i : processes){
            if(i->getReadyTime()<=currentTime && i->getExecutionTime()>0){
                noProcessReady = 0;
                currentTime += i->getExecutionTime();
                i->setExecutionTime(0);
                responseTime += (currentTime - i->getReadyTime());
                
                if (processSkipped){
                    processSkipped = 0;
                    break;
                }
            }
            else if (i->getReadyTime() > currentTime){
                processSkipped = 1;
            }
        }
        if(noProcessReady){
            currentTime ++; //stall
        }
    }

    double avgRTime = responseTime/nrProcesses;
    return avgRTime;
}

double schedulingStrategy::getAvgResponseTimePmt(){
    int responseTime = 0, currentTime = 0;
    int nrProcesses = processes.size();
    bool processSkipped = 0;

    while([&]() -> bool {
            int totalExecutionTime = 0;

            for(const auto& i : processes){
                totalExecutionTime += i->getExecutionTime();}
        
            return totalExecutionTime > 0;}()){
        
        bool noProcessReady=1;
        for(const auto& i : processes){
            if(i->getReadyTime()<=currentTime && i->getExecutionTime()>0){
                noProcessReady = 0;

                if (processSkipped){
                    currentTime ++;
                    i->setExecutionTime(i->getExecutionTime() - 1);
                    if (i->getExecutionTime() == 0){
                        responseTime += (currentTime - i->getReadyTime());
                    }
                    sortProcesses();
                    break;
                }
                else{
                    currentTime += i->getExecutionTime();
                    i->setExecutionTime(0);
                    responseTime += (currentTime - i->getReadyTime());
                }
            }
            else if (i->getReadyTime() > currentTime){
                processSkipped = 1;
            }
        }
        if(noProcessReady){
            currentTime ++; //stall
        }
    }
    return static_cast<double>(responseTime)/nrProcesses;
}