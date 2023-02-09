#include "input_gen_rand.h"
#include <stdlib.h>

RandomGenerator::RandomGenerator(sc_module_name name) : sc_module{name} {

  for (size_t i{0}; i < 4; ++i) {
    car_signals[i].initialize(false);
  }

  SC_THREAD(generator_thread);
}

void RandomGenerator::generator_thread() {

  int counters[4]{};
  for (;;) {
    wait(1, SC_SEC);
    // std::cout << sc_time_stamp() << std::endl;
    for (size_t i{0}; i < 4; ++i) {
      if (traffic_lights[i]->read() == GREEN) {
        if (--counters[i] <= 0) {
          car_signals[i]->write(false);
        }
      } else {
        bool value{rand() % 100};
        if (value < RATE) {
          counters[i] = rand() % MAX_CARS + 1;
          car_signals[i]->write(true);
        }
      }
    }
  }
}
