#ifndef PROCESSOR_H
#define PROCESSOR_H

class Processor {
 public:
  float Utilization();

 private:
  float Previdle, PrevNonidle, PrevTotal;
};

#endif