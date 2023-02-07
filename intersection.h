#pragma once
#include <systemc.h>

#define RED false
#define GREEN true

typedef bool LightColour;

SC_MODULE(Intersection) {
  sc_out<bool> lights[4];
  bool lights_local[4];
  sc_in<bool> car_status[4];
  int timers[4];

  SC_HAS_PROCESS(Intersection);
  Intersection(sc_module_name name);

  void logic_method();
  void timeout_thread();
};
