#include <systemc.h>
#include "lights.h"
#include <iostream>

SC_MODULE(Monitor) {
  sc_in<bool> car_status[4];

  sc_in<bool> traffic_lights[4];

  std::ostream& os{std::cout};

  SC_HAS_PROCESS(Monitor);
  Monitor(sc_module_name name);

  void check_traffic_lights_status();
  void check_generated_inputs();
};
