#include <string>

#include "format.h"

using std::string;


string Format::ElapsedTime(long seconds) { 
    int hour, minutes, sec;
    string timestring;
    hour = seconds/3600;
    minutes = (seconds - hour * 3600)/ 60;
    sec = seconds - (hour*3600 + minutes*60);
    timestring = std::to_string(hour) + ":" + std::to_string(minutes) + ":" + std::to_string(sec);
    return timestring;

 }