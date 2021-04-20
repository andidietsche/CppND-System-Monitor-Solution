#include "processor.h"

#include <vector>

#include "linux_parser.h"

// TODO: Return the aggregate CPU utilization
float Processor::Utilization() {
  // float test =
  // (LinuxParser::Jiffies()-LinuxParser::IdleJiffies())/LinuxParser::Jiffies();
  // return test;
  float Idle, Nonidle,Total,PrevIdle,PrevNonidle,totaled, idled,PrevTotal, cpu_utilization; 

  std::vector<std::string> cpu_usage = LinuxParser::CpuUtilization();
  PrevIdle = 0.0;
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
    idled = Idle - PrevIdle;

    cpu_utilization = (totaled - idled)/totaled;

    PrevIdle = Idle;
    PrevNonidle = Nonidle;
    PrevTotal = Total;

    return cpu_utilization;
    }