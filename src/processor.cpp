#include "processor.h"

#include <vector>

#include "linux_parser.h"

// Done: Return the aggregate CPU utilization
float Processor::Utilization() {
  float Idle, Nonidle, Total, totaled, idled, cpu_utilization;

  std::vector<std::string> cpu_usage = LinuxParser::CpuUtilization();
  Previdle = 0.0;
  PrevNonidle = 0.0;
  PrevTotal = 0.0;

  Idle = std::stof(cpu_usage[LinuxParser::kIdle_]) +
         std::stof(cpu_usage[LinuxParser::kIOwait_]);

  Nonidle = std::stof(cpu_usage[LinuxParser::kUser_]) +
            std::stof(cpu_usage[LinuxParser::kNice_]) +
            std::stof(cpu_usage[LinuxParser::kIRQ_]) +
            std::stof(cpu_usage[LinuxParser::kSoftIRQ_]) +
            std::stof(cpu_usage[LinuxParser::kSystem_]) +
            std::stof(cpu_usage[LinuxParser::kSteal_]);

  Total = Idle + Nonidle;
  totaled = Total - PrevTotal;
  idled = Idle - Previdle;

  cpu_utilization = (totaled - idled) / totaled;

  Previdle = Idle;
  PrevNonidle = Nonidle;
  PrevTotal = Total;

  return cpu_utilization;
}