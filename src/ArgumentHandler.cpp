#include <string>
#include <thread>

#include "ArgumentHandler.h"
#include "SJF.h"
#include "FCFS.h"
#include "EDF.h"
#include "LLF.h"
#include "RoundRobin.h"

ArgumentHandler::ArgumentHandler(int argc, char* argv[]){
    quantum = 2; //default setting if not specified
    preemptive = false; //default setting if not specified

    for (int i = 1; i < argc; ++i) {
        if (static_cast<std::string>(argv[i]) == "-h"){
            printHelp();
            std::exit(0);
        }
        else if(static_cast<std::string>(argv[i]) == "--preemptive"){
            preemptive = true;
        }
        else if (static_cast<std::string>(argv[i]) == "-p") {
            // Handle multiple parameters following -p
            ++i; // Move to next argument after -p
            while (i < argc && argv[i][0] != '-') {
                processParameters.push_back(static_cast<std::string>(argv[i]));
                ++i;
            }
            --i; // Move back to last valid argument
        } 
        else if (static_cast<std::string>(argv[i]) == "-s") {
            // Handle parameter following -s
            ++i; // Move to next argument after -s
            if (i < argc && argv[i][0] != '-') {
                strategy = static_cast<std::string>(argv[i]);
            } else {
                throw std::invalid_argument("-s requires a single parameter");
            }
        } 
        else if (static_cast<std::string>(argv[i]) == "-q") {
            // Handle parameter following -q
            ++i; // Move to next argument after -q
            if (i < argc && argv[i][0] != '-') {
                try{
                    quantum = stoi(static_cast<std::string>(argv[i]));
                }
                catch (const std::invalid_argument& ia) {
                    throw std::invalid_argument("Invalid argument(s) following -p");
                } 
                catch (const std::out_of_range& oor) {
                    throw std::invalid_argument("Invalid argument(s) following -p: Out of range error");
                }
                if (quantum <= 0){
                    throw std::invalid_argument("Invalid argument following -q. Has to be 1 or higher");
                }
            } else {
                throw std::invalid_argument("-q requires a single parameter");
            }
        } 
        else {
            throw std::invalid_argument("Unknown argument");
        }
    }
}

void ArgumentHandler::processArguments(){
    try{
        if (processParameters.empty()){
            throw(std::invalid_argument("Process parameters are missing."));
        }
        else{
            createProcesses();
        }
        simulateScheduling();
    }
    catch (std::invalid_argument& msg){
        throw std::invalid_argument(msg.what());
    }
}

void ArgumentHandler::createProcesses(){
    if(processParameters.size() % 4 != 0){
        throw std::invalid_argument("Invalid number of arguments following -p");
    }
    
    for (int i = 0; i < processParameters.size()-3; i+=4){
        int readyTime = 0, executionTime = 0, deadline = 0;
        std::string processName = processParameters[i];
        try {
            readyTime = std::stoi(processParameters[i+1]);
            executionTime = std::stoi(processParameters[i+2]);
            deadline = std::stoi(processParameters[i+3]);
        } 
        catch (const std::invalid_argument& ia) {
            throw std::invalid_argument("Invalid argument(s) following -p");
        } 
        catch (const std::out_of_range& oor) {
            throw std::invalid_argument("Invalid argument(s) following -p: Out of range error");
        }
        
        std::shared_ptr<Process> p = std::make_shared<Process>(processName, readyTime, executionTime, deadline);
        processes.push_back(p);
    }

    //printing initial process details
    std::cout << std::endl << "--------------------------------------------------" << std::endl;
    std::cout << "Initial state" << std::endl;
    std::cout << "--------------------------------------------------" << std::endl;
    printProcesses(processes);
}

void ArgumentHandler::simulateScheduling(){
    bool invalidArg = 1;
    std::vector<std::thread> threads;

    if (strategy.empty()){
        invalidArg = 0;

        threads.emplace_back([&] {
            FCFS fcfs(processes, preemptive);
            printResults("FCFS", fcfs);
        });
        threads.emplace_back([&] {
            SJF sjf(processes, preemptive);
            printResults("SJF", sjf);
        });
        threads.emplace_back([&] {
            EDF edf(processes, preemptive);
            printResults("EDF", edf);
        });
        threads.emplace_back([&] {
            LLF llf(processes, preemptive);
            printResults("LLF", llf);
        });
        threads.emplace_back([&] {
            RoundRobin rr(processes, quantum);
            printResults("Round Robin", rr);
        });
    }
    else{
        if(strategy.contains("FCFS")){
            invalidArg = 0;
            threads.emplace_back([&] {
                FCFS fcfs(processes, preemptive);
                printResults("FCFS", fcfs);
            });
        }
        if(strategy.contains("SJF")){
            invalidArg = 0;
            threads.emplace_back([&] {
                SJF sjf(processes, preemptive);
                printResults("SJF", sjf);
            });
        }
        if(strategy.contains("EDF")){
            invalidArg = 0;
            threads.emplace_back([&] {
                EDF edf(processes, preemptive);
                printResults("EDF", edf);
            });
        }
        if(strategy.contains("LLF")){
            invalidArg = 0;
            threads.emplace_back([&] {
                LLF llf(processes, preemptive);
                printResults("LLF", llf);
            });
        }
        if(strategy.contains("RoundRobin")){
            invalidArg = 0;
            threads.emplace_back([&] {
                RoundRobin rr(processes, quantum);
                printResults("Round Robin", rr);
            });
        }
    }
    for (auto& thread : threads){
        thread.join();
     }   
    if(invalidArg){
        throw std::invalid_argument("Invalid Argument following -s");
    }
}

void ArgumentHandler::printHelp(){
    std::cout << std::endl;
    std::cout << "Usage:" << std::endl;
    std::cout << "\tscheduling [OPTIONS]" << std::endl << std::endl;
    std::cout << "Description:" << std::endl;
    std::cout << "\tCalculating the average response time of processes using different scheduling strategies." << std::endl << std::endl;
    std::cout << "\t-h\tDisplay this help." << std::endl;
    std::cout << "\t-p\tSpecify one or multiple processes. Followed by [process name] [ready time] [execution time] [deadline]. \n\t\tYou may add as many processes as you like. This option is mandatory." << std::endl;
    std::cout << "\t-q\tSet a quantum for Round Robin. Default is 2 if omitted." << std::endl;
    std::cout << "\t-s\tSpecify one or multiple scheduling strategies separated by comma. \n\t\tPossible strategies: FCFS,SJF,EDF,LLF,RoundRobin. If not specified, all of them are selected." << std::endl << std::endl;
    std::cout << "\t--preemptive\tActivate preemtive mode for the scheduling strategies." << std::endl << std::endl ;
    std::cout << "Examples:" << std::endl;
    std::cout << "\tscheduling -h\t\t\t\t\t\tDisplay this help." << std::endl;
    std::cout << "\tscheduling -p p1 0 4 10 p2 0 5 8\t\t\tSpecify two processes, using all strategies." << std::endl;
    std::cout << "\tscheduling -p p1 0 4 10 p2 0 5 8 -s RoundRobin -q 5\tSpecify two processes, using RoundRobin with a quantum of 5." << std::endl;
    std::cout << "\tscheduling -p p1 0 4 10 p2 0 5 8 -s FCFS,EDF\t\tSpecify two processes, using FCFS and EDF as strategies." << std::endl << std::endl;
}

void ArgumentHandler::printProcesses(const std::vector<std::shared_ptr<Process>>& proc) const{
    std::cout << std::endl;
    std::cout << "Process | Ready Time | Execution Time | Deadline" << std::endl;    
    for (auto& i : proc){
        std::cout << "   " << i->getName() << "\t     " <<
            i->getReadyTime() << "\t\t   " << 
            i->getExecutionTime() << "\t\t  " << 
            i->getDeadline() << 
            std::endl;
    }
    std::cout << std::endl;
}

void ArgumentHandler::printResults(std::string strategy, schedulingStrategy& obj){
    std::lock_guard<std::mutex> lock(resultsMutex); //lock the mutex
    std::cout << std::endl << "--------------------------------------------------" << std::endl;
    std::cout << strategy << std::endl;
    std::cout << "--------------------------------------------------" << std::endl;
    printProcesses(obj.getProcesses());
    std::cout << "Average response time: " << obj.getAvgResponseTime() << std::endl;
    //mutex is automatically released when 'lock' goes out of scope
}

int main(int argc, char* argv[]){
    try{
        ArgumentHandler argHandler(argc, &argv[0]);
        argHandler.processArguments();
    }
    catch(std::invalid_argument& msg){
        std::cerr << std::endl << "Error: " << msg.what() << std::endl;
        std::cerr << std::endl << "Use -h to display help" << std::endl << std::endl;
    }

    return 0;
}