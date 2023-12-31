# Process Scheduling

## Description
Minimal process scheduling simulator able to calculate the avarage response time of multiple processes inside one CPU.<br />
The processes are defined by name, ready time, execution time and deadline.<br />
Supports FCFS, SJF, EDF, LLF and Round Robin.<br />
Preemptive and non-preemptive simulation possible.

## Getting Started
```
git clone <repo>
cmake -S . -B ./build
cd ./build
cmake --build .
scheduling -h
```

## Requirements
git<br />
cmake