#include "process.h"

#include <unistd.h>

#include <cctype>
#include <sstream>
#include <string>
#include <vector>

#include "format.h"
#include "linux_parser.h"

using std::string;
using std::to_string;
using std::vector;

// Done: Return this process's ID
int Process::Pid() { return pid_; }

// Done: Return this process's CPU utilization
float Process::CpuUtilization() {
  float total_time =
      LinuxParser::ActiveJiffies(this->pid_) / sysconf(_SC_CLK_TCK);
  float uptime_proc = LinuxParser::UpTime();

  return total_time / uptime_proc;
}

// Done: Return the command that generated this process
string Process::Command() { return this->command_; }

// Done: Return this process's memory utilization
string Process::Ram() { return LinuxParser::Ram(pid_); }

// Done: Return the user (name) that generated this process
string Process::User() { return this->user_; }  // LinuxParser::User(pid_)

// Done: Return the age of this process (in seconds)
long int Process::UpTime() {
  return LinuxParser::UpTime() - LinuxParser::UpTime(pid_);
}
// Done: Overload the "less than" comparison operator for Process objects
bool Process::operator<(Process const& a) const {
  return (a.cpuUtilization_ < cpuUtilization_);
}