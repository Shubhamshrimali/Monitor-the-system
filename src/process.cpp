#include <unistd.h>
#include <cctype>
#include <sstream>
#include <string>
#include <vector>

#include "process.h"
#include "linux_parser.h"
using std::string;
using std::to_string;
using std::vector;

Process::Process(int pid):processId_(pid){
    calculateCpuUsage();
    determineCommand();
    determineRam();
    determineUptime();
    determineUser();
}
// TODO: Return this process's ID
int Process::Pid() { return processId_; }

// TODO: Return this process's CPU utilization
float Process::CpuUtilization() { return cpuUsage_; }

// TODO: Return the command that generated this process
string Process::Command() { return command_; }

// TODO: Return this process's memory utilization
string Process::Ram() { return ram_; }

// TODO: Return the user (name) that generated this process
string Process::User() { return user_; }

// TODO: Return the age of this process (in seconds)
long int Process::UpTime() { return uptime_; }

// TODO: Overload the "less than" comparison operator for Process objects
// REMOVE: [[maybe_unused]] once you define the function
bool Process::operator<(Process const& a[[maybe_unused]]) const { return true; }

void Process::calculateCpuUsage(){
    long uptime=LinuxParser::UpTime();
    vector<float> value=LinuxParser::CpuUtilization(Pid());
    if(value.size()==5){
        float T_time=value[kUtime_]+value[kStime_]+value[kCutime_]+value[kCstime_];
        float sec=uptime-value[kStarttime_];
        cpuUsage_=T_time/sec;
    }
    else{
        cpuUsage_=0;
    }
}
void Process::determineUser() { 
    user_ = LinuxParser::User(Pid()); 
    }
void Process::determineCommand() { 
    command_ = LinuxParser::Command(Pid()); 
    }
void Process::determineRam() {
  string res = LinuxParser::Ram(Pid());
  try {
    long val = std::stol(res) / 1000;
    ram_ = std::to_string(val);
  } catch (const std::invalid_argument& arg) {
    ram_ = "0";
  }
}
void Process::determineUptime() {
  uptime_ = LinuxParser::UpTime(Pid());
}