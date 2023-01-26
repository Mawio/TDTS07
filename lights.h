#pragma once

#include <systemc.h>

enum class LightColour {
  GREEN,
  RED
};

SC_MODULE(TrafficLight) {
  sc_out<LightColour> output;
  sc_in<LightColour> opposite;
  sc_in<LightColour> orthogonal_left;
  sc_in<LightColour> orthogonal_right;
  sc_in<bool> car_status;

  SC_HAS_PROCESS(TrafficLight);
  TrafficLight(sc_module_name name, LightColour colour);

  void orthogonal_changed_method();
  void car_status_changed_method();
};
