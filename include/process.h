#ifndef PROCESS_H
#define PROCESS_H

#include <string>
/*
Basic class for Process representation
It contains relevant attributes as shown below
*/
class Process {
 public:
  int Pid();                               // TODO: See src/process.cpp
  std::string User();                      // TODO: See src/process.cpp
  std::string Command();                   // TODO: See src/process.cpp
  float CpuUtilization();                  // TODO: See src/process.cpp
  std::string Ram();                       // TODO: See src/process.cpp
  long int UpTime();                       // TODO: See src/process.cpp
  bool operator<(Process const& a) const;  // TODO: See src/process.cpp
  Process(int pid);

  // TODO: Declare any necessary private members
 private:
int processId_;
  std::string user_;
  std::string command_;
  float cpuUsage_;
  std::string ram_;
  long uptime_;
  enum ProcessCPUStates {
    kUtime_ = 0,
    kStime_,
    kCutime_,
    kCstime_,
    kStarttime_
  };
  void calculateCpuUsage();
  void determineUser();
  void determineCommand();
  void determineRam();
  void determineUptime();
};

#endif