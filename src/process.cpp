#include "process.h"

#include <unistd.h>

#include <cctype>
#include <sstream>
#include <string>
#include <vector>

#include "linux_parser.h"

using std::string;
using std::to_string;
using std::vector;

// TODO: Return this process's ID
int Process::Pid() { return pid_; }  // 0

// TODO: Return this process's CPU utilization
float Process::CpuUtilization() {
  string line, word, pidstring;
  float total_time,seconds, cpu_usage;
  float utime, stime,cutime,cstime,starttime;
  vector<string> statdata;
  std::stringstream ss;
  ss << pid_;
  std::ifstream stream(LinuxParser::kProcDirectory + pidstring +
                       LinuxParser::kStatFilename);
  if (stream.is_open()) {
    while (std::getline(stream, line)) {
      std::istringstream linestream(line);
      while (linestream >> word) {
        statdata.push_back(word);
      }
    }
  }
  utime = std::stof(statdata[13]);
  stime = std::stof(statdata[14]);
  cutime = std::stof(statdata[15]);
  cstime = std::stof(statdata[16]);
  starttime = std::stof(statdata[21]);


  total_time = utime + stime + cutime + cstime;
  seconds = LinuxParser::UpTime()-(starttime/100); //100 instead of sysconf(_SC_CLK_TCK)
  cpu_usage = 100*((total_time/100)/seconds);
  return cpu_usage;
}

// TODO: Return the command that generated this process
string Process::Command() { return LinuxParser::Command(pid_); }

// TODO: Return this process's memory utilization
string Process::Ram() { return LinuxParser::Ram(pid_); }

// TODO: Return the user (name) that generated this process
string Process::User() { return LinuxParser::User(pid_); }

// TODO: Return the age of this process (in seconds)
long int Process::UpTime() {
  return LinuxParser::UpTime() - LinuxParser::UpTime(pid_);
}

// TODO: Overload the "less than" comparison operator for Process objects
// REMOVE: [[maybe_unused]] once you define the function
bool Process::operator<(Process const& a [[maybe_unused]]) const {
//   float &bCpu = CpuUtilization();
//   float &aCpu = a.CpuUtilization();
//   return &bCpu> &aCpu;
return 0;
}