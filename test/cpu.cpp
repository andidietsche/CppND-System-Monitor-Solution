#include <unistd.h>

#include <cctype>
#include <sstream>
#include <string>
#include <vector>
#include <fstream>
#include <iostream>


int main(){

std::string line, word, pidstring;
  float total_time,seconds, cpu_usage;
  float utime, stime,cutime,cstime,starttime;
  std::vector<std::string> statdata;
 
  std::ifstream stream("/proc/13217/stat");
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
  seconds = 37137-(starttime/sysconf(_SC_CLK_TCK)); //100 instead of sysconf(_SC_CLK_TCK)
  cpu_usage = 100*((total_time/sysconf(_SC_CLK_TCK))/seconds);
  std::cout<< "CpuUsage: " << cpu_usage<< std::endl;;




}