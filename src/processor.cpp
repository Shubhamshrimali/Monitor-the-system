#include "processor.h"
#include <string>
#include <vector>
#include "linux_parser.h"

using std::string;
using std::vector;

Processor::Processor() : preTotalCpuTime(0.0),preIdleCpuTime(0.0){};

float Processor::Utilization() {
  vector<long> cpu = convertToLong(LinuxParser::CpuUtilization());
  float totalCpuTime =
      cpu[LinuxParser::kUser_] + cpu[LinuxParser::kNice_] +
      cpu[LinuxParser::kSystem_] + cpu[LinuxParser::kIdle_] +
      cpu[LinuxParser::kIOwait_] + cpu[LinuxParser::kIRQ_] +
      cpu[LinuxParser::kSoftIRQ_] + cpu[LinuxParser::kSteal_];
  float CpuTime =cpu[LinuxParser::kIdle_] + cpu[LinuxParser::kIOwait_];

  float diffIdle = CpuTime - preIdleCpuTime;
  float diffTotal = totalCpuTime - preTotalCpuTime;
  float diffUsage = (diffTotal - diffIdle) / diffTotal;
  preIdleCpuTime = CpuTime;
  preTotalCpuTime = totalCpuTime;
  return diffUsage;
}

vector<long> Processor::convertToLong(vector<string> values) {
  vector<long> convertedResult{};

  for (int it = 0; it < (int)values.size(); it++) {
    try {
      convertedResult.push_back(std::stol(values[it]));
    } catch (const std::invalid_argument& arg) {
      convertedResult.push_back((long)0);
    }
  }
  return convertedResult;
}