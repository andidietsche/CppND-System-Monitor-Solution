#include <string>
#include <iomanip>
#include <iostream>

#include "format.h"

using std::string;


string Format::ElapsedTime(long seconds) { 
    int hour, minutes, sec;
    string timestring;
    hour = seconds/3600;
    minutes = (seconds - hour * 3600)/ 60;

    sec = seconds - (hour*3600 + minutes*60);
 

    std::ostringstream stream;
      stream << std::setw(2) << std::setfill('0') << hour << ":" 
     << std::setw(2) << std::setfill('0') << minutes << ":"
     << std::setw(2) << std::setfill('0') << sec;
  return stream.str();

 }