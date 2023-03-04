#pragma once
#include "intersection.h"
#include <fstream>

SC_MODULE(DeterministicGenerator) {

  sc_out<bool> car_signals[4];
  sc_in<bool> traffic_lights[4];
  int car_counts[4];

  SC_HAS_PROCESS(DeterministicGenerator);
  DeterministicGenerator(sc_module_name name, std::ifstream ifs);

  void generator_thread();
};
