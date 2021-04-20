#include "linux_parser.h"

#include <dirent.h>
#include <unistd.h>

#include <map>
#include <string>
#include <vector>

using std::stof;
using std::string;
using std::to_string;
using std::vector;

// DONE: An example of how to read data from the filesystem
string LinuxParser::OperatingSystem() {
  string line;
  string key;
  string value;
  std::ifstream filestream(kOSPath);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::replace(line.begin(), line.end(), ' ', '_');
      std::replace(line.begin(), line.end(), '=', ' ');
      std::replace(line.begin(), line.end(), '"', ' ');
      std::istringstream linestream(line);
      while (linestream >> key >> value) {
        if (key == "PRETTY_NAME") {
          std::replace(value.begin(), value.end(), '_', ' ');
          return value;
        }
      }
    }
  }
  return value;
}

// DONE: An example of how to read data from the filesystem
string LinuxParser::Kernel() {
  string os, version, kernel;
  string line;
  std::ifstream stream(kProcDirectory + kVersionFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);
    linestream >> os >> version >> kernel;
  }
  return kernel;
}

// BONUS: Update this to use std::filesystem
vector<int> LinuxParser::Pids() {
  vector<int> pids;
  DIR* directory = opendir(kProcDirectory.c_str());
  struct dirent* file;
  while ((file = readdir(directory)) != nullptr) {
    // Is this a directory?
    if (file->d_type == DT_DIR) {
      // Is every character of the name a digit?
      string filename(file->d_name);
      if (std::all_of(filename.begin(), filename.end(), isdigit)) {
        int pid = stoi(filename);
        pids.push_back(pid);
      }
    }
  }
  closedir(directory);
  return pids;
}

float LinuxParser::MemoryUtilization() {
  std::map<string, string> memdata;
  std::string line;
  std::string key;
  float memtotal, memfree, diff;
  string value;

  std::ifstream stream(kProcDirectory + kMeminfoFilename);
  if (stream.is_open()) {
    while (std::getline(stream, line)) {
      std::replace(line.begin(), line.end(), ':', ' ');
      std::istringstream linestream(line);
      while (linestream >> key >> value) {
        memdata[key] = value;
      }
    }
    memtotal = std::stof(memdata["MemTotal"]);
    memfree = std::stof(memdata["MemFree"]);
  }
  diff = memtotal - memfree;
  return diff / memtotal;
}

long LinuxParser::UpTime() {//in seconds
  string line;
  string uptimestring, idletime;
  long uptime;
  std::ifstream filestream(kProcDirectory + kUptimeFilename);
  if (filestream.is_open()) {
    std::getline(filestream, line);
    std::istringstream linestream(line);
    linestream >> uptimestring >> idletime;
  }

  uptime = std::stol(uptimestring);
  return uptime;
}

long LinuxParser::Jiffies() {
  return ActiveJiffies() + IdleJiffies();
}  // sum of Active and Idle jiffies

// TODO: Read and return the number of active jiffies for a PID
// REMOVE: [[maybe_unused]] once you define the function
long LinuxParser::ActiveJiffies(int pid [[maybe_unused]]) { return 0; }

long LinuxParser::ActiveJiffies() {
  return 0;
  // vector<string> Jifs = LinuxParser::CpuUtilization();  // stores every thing
  // from proc/stat's
  //                                     // first line as a string
  // }
  // long ActiveJiffies = std::stol(Jifs[LinuxParser::kUser_]) +
  // std::stol(Jifs[LinuxParser::kNice_]) +
  // std::stol(Jifs[LinuxParser::kSystem_]) +
  //                      std::stol(Jifs[LinuxParser::kIRQ_]) +
  //                      std::stol(Jifs[LinuxParser::kSoftIRQ_]) +
  //                      std::stol(Jifs[LinuxParser::kSteal_]);
  // return ActiveJiffies;
}

long LinuxParser::IdleJiffies() {
  return 0;  // idle+ iowait
  // std::string name, user, nice, system, idle, iowait, irq, softirq, steal,
  //     guest, guest_size, line;

  // std::ifstream stream(kProcDirectory + kStatFilename);
  // if (stream.is_open()) {
  //   std::getline(stream, line);
  //   std::istringstream linestream(line);
  //   linestream >> name >> user >> nice >> system >> idle >> iowait >> irq >>
  //       softirq >> steal >> guest >> guest_size;
  // }
  // long IdleJiffies = std::stol(idle) + std::stol(iowait);
  // return IdleJiffies;
}

vector<string> LinuxParser::CpuUtilization() {
  string line, word;
  std::vector<string> cpu_utility;
  std::ifstream stream(kProcDirectory + kStatFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);
    while (linestream >> word) {
      cpu_utility.push_back(word);  // store each word form first line
    }
  }
  return cpu_utility;
}

int LinuxParser::TotalProcesses() {
  string line, key, value;
  std::map<string, string> stats;
  std::ifstream filestream(kProcDirectory + kStatFilename);

  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::istringstream linestream(line);
      while (linestream >> key >> value) {
        stats[key] = value;
      }
    }
  }
  return std::stoi(stats["processes"]);
}

//Done
int LinuxParser::RunningProcesses() {
  string line, key, value;
  std::map<string, string> stats;
  std::ifstream filestream(kProcDirectory + kStatFilename);

  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::istringstream linestream(line);
      while (linestream >> key >> value) {
        stats[key] = value;
      }
    }
  }
  return std::stoi(stats["procs_running"]);
}









// Done: Read and return the command associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Command(int pid) {
  std::string cmdline, line;
  std::stringstream filename;
  filename << kProcDirectory << "/" << pid << "/" << kCmdlineFilename;
  std::ifstream stream(filename.str());
  if (stream.is_open()) {
    std::getline(stream, line);
  } else {
    return "N/A";
  }
  return line;
}
// Done: Read and return the memory used by a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Ram(int pid) {
  std::string line, key, value;
  std::stringstream filename;
  filename << kProcDirectory << "/" << pid << "/" << kStatusFilename;
  std::ifstream stream(filename.str());
  if (stream.is_open()) {
    while (std::getline(stream, line)) {
      std::istringstream linestream(line);
      while (linestream >> key >> value) {
        if (key == "VmSize:") {
          return to_string(std::stoi(value) / 1024);
        }
      }
    }
  } else {
    return "N/A";
  }
}

// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Uid(int pid) {
  std::map<std::string, std::string> data;
  std::string line, value, key, pidstring, uid;
  std::stringstream ss;
  ss << pid;
  pidstring = ss.str();

  std::ifstream stream(kProcDirectory + pidstring + kStatusFilename);
  if (stream.is_open()) {
    while (std::getline(stream, line)) {
      std::replace(line.begin(), line.end(), ':', ' ');
      std::istringstream linestream(line);
      while (linestream >> key >> value) {
        data[key] = value;
      }
    }
    uid = data["Uid"];
  }
  return uid;
}

// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::User(int pid) {
  std::string line, user;
  std::ifstream stream(kPasswordPath);
  std::stringstream searchstring;
  searchstring << ":x:" + LinuxParser::Uid(pid);

  std::string search = searchstring.str();
  if (stream.is_open()) {
    while (std::getline(stream, line)) {
      if (line.find(search) != std::string::npos) {
        int pos = line.find(search);
        user = line.substr(0, pos);
      }
      else continue;
    }
  }
  return user;
}

// Done: Read and return the uptime of a process
// REMOVE: [[maybe_unused]] once you define the function
long LinuxParser::UpTime(int pid) {
  long uptime{0};
  string line, word;
  vector<string> data;
  std::stringstream filename;
  filename << kProcDirectory << "/" << pid << "/" << kStatFilename;
  std::ifstream stream(filename.str());
  if (stream.is_open()) {
    while (std::getline(stream, line)) {
      std::stringstream linestream(line);
      while (linestream >> word) {
        data.push_back(word);
      }
    }
    uptime = std::stol(data[21]) / sysconf(_SC_CLK_TCK);  // to get seconds
  }

  return uptime;
}
