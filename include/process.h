#ifndef PROCESS_H
#define PROCESS_H

#include <string>

#include "linux_parser.h"
/*
Basic class for Process representation
It contains relevant attributes as shown below
*/
class Process {
 public:
  void setPid(int pid) { pid_ = pid; }
  void setUser(int pid) { user_ = LinuxParser::User(pid); }
  void setCommand(int pid) { command_ = LinuxParser::Command(pid); }
  void setCpuUilization() { cpuUtilization_ = CpuUtilization(); }

  // float getcpuUtilization();
  int Pid();                               // Done: See src/process.cpp
  std::string User();                      // Done: See src/process.cpp
  std::string Command();                   // Done: See src/process.cpp
  float CpuUtilization();                  // Done: See src/process.cpp
  std::string Ram();                       // Done: See src/process.cpp
  long int UpTime();                       // Done: See src/process.cpp
  bool operator<(Process const& a) const;  // Done: See src/process.cpp

  // Done: Declare any necessary private members
 private:
  int pid_;
  float cpuUtilization_ = 0;
  std::string user_{""};
  std::string command_{""};
};

#endif