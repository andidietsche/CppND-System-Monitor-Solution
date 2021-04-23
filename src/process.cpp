#include "process.h"

#include <unistd.h>

#include <cctype>
#include <sstream>
#include <string>
#include <vector>

#include "linux_parser.h"
#include "format.h"

using std::string;
using std::to_string;
using std::vector;


//float Process::getcpuUtilization(){return cpuUtilization_;}

// TODO: Return this process's ID
int Process::Pid() { return pid_; }  // 0

// TODO: Return this process's CPU utilization
float Process::CpuUtilization() {
 float uptime_proc = LinuxParser::UpTime(pid_);
 float total_time = LinuxParser::ActiveJiffies(pid_);
 float CpuUtility =100*((total_time/sysconf(_SC_CLK_TCK))/uptime_proc);

 return CpuUtility;

}

// TODO: Return the command that generated this process
string Process::Command() { return LinuxParser::Command(pid_); }

// TODO: Return this process's memory utilization
string Process::Ram() { return LinuxParser::Ram(pid_); }

// TODO: Return the user (name) that generated this process
string Process::User() { return LinuxParser::User(pid_); }

// TODO: Return the age of this process (in seconds)
long int Process::UpTime() {
  long int time;
   return LinuxParser::UpTime() - LinuxParser::UpTime(pid_);
}
// TODO: Overload the "less than" comparison operator for Process objects
// REMOVE: [[maybe_unused]] once you define the function
bool Process::operator<(Process const& a) const {

return (cpuUtilization_ < a.cpuUtilization_);
}