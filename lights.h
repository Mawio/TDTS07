#pragma once
#include <systemc.h>

#define RED false
#define GREEN true

typedef bool LightColour;

SC_MODULE(TrafficLight) {
  sc_out<LightColour> output;
  sc_in<LightColour> opposite;
  sc_in<LightColour> orthogonal_left;
  sc_in<LightColour> orthogonal_right;
  sc_in<bool> car_status;

  SC_HAS_PROCESS(TrafficLight);
  TrafficLight(sc_module_name name);

  void light_logic_method();
  void light_logic_thread();
};
