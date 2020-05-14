#ifndef PROCESSOR_H
#define PROCESSOR_H

#include <string>
#include <vector>

using std::string;
using std::vector;

class Processor {
 public:
  float Utilization();  // TODO: See src/processor.cpp
  Processor();
  // TODO: Declare any necessary private members
 private:
 float preTotalCpuTime;
 float preIdleCpuTime;
 vector<long> convertToLong(vector<string> values);
};

#endif