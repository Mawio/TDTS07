#include "input_gen_deterministic.h"

DeterministicGenerator::DeterministicGenerator(sc_module_name name,
                                               std::ifstream ifs)
    : sc_module{name} {
  for (size_t i = 0; i < 4; ++i) {
    ifs >> car_counts[i];
    car_signals[i].initialize(false);
  }

  SC_THREAD(generator_thread);
}

void DeterministicGenerator::generator_thread() {
  for (;;) {
    wait(1, SC_SEC);
    for (size_t i{}; i < 4; ++i) {
      // A light is green so a car will leave
      if (traffic_lights[i]->read() == GREEN) {
        // The last car left in the last time step, so we have to notify the light
        if (car_counts[i] == 0) {
          car_signals[i].write(false);
        } else {
          car_counts[i]--;
        }
      }
      // If a light is red, there are cars there but we didn't notify the light yet
      else if (car_counts[i] > 0 && !car_signals[i].read()) {
          car_signals[i].write(true);
      }
    }
  }
}
