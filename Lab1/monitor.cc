#include "monitor.h"

Monitor::Monitor(sc_module_name name, int timeout) : sc_module(name), timers{}, timeout{timeout} {

  SC_METHOD(check_traffic_lights_status);
  dont_initialize();
  for (size_t i{0}; i < 4; ++i) {
    sensitive << traffic_lights[i];
  }
}

void Monitor::check_traffic_lights_status() {

  os << "At time: " << sc_time_stamp() << std::endl;

  for (size_t i{0}; i < 4; ++i) {
    auto &&traffic_light{traffic_lights[i]};

    // Assert property 1 and 2
    if (traffic_light->read() == GREEN) {
      assert(traffic_lights[(i + 1) % 4]->read() == RED);
      assert(traffic_lights[(i + 3) % 4]->read() == RED);
    }

    // Reset the timer used to check for timeout
    if (traffic_light->read() == RED) {
      timers[i] = 0;
    }

    // Assert property 3 by ensuring timeouting
    if (traffic_light->read() == GREEN) {
      assert(timers[i]++ <= this->timeout);
    }

    // Assert that lights will only be green if there is demand
    if (traffic_light->read() == GREEN) {
      assert(car_status[i]->read());
    }

    os << i << ": " << (traffic_light->read() ? "GREEN" : "RED") << ";"
       << (car_status[i]->read() ? "Cars here" : "No cars") << std::endl;
  }
}
