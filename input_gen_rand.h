#pragma once
#include "lights.h"

SC_MODULE(RandomGenerator) {

  sc_out<bool> car_signals[4];
  sc_in<LightColour> traffic_lights[4];

  SC_HAS_PROCESS(RandomGenerator);
  RandomGenerator(sc_module_name name);

  void generator_thread();

};
