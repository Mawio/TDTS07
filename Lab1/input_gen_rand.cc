#include "input_gen_rand.h"
#include <stdlib.h>

RandomGenerator::RandomGenerator(sc_module_name name, int max_cars, int rate)
    : sc_module{name}, max_cars{max_cars}, rate{rate} {

  for (size_t i{0}; i < 4; ++i) {
    car_signals[i].initialize(false);
  }

  SC_THREAD(generator_thread);
}

void RandomGenerator::generator_thread() {

  int counters[4]{};
  for (;;) {
    wait(1, SC_SEC);
    for (size_t i{0}; i < 4; ++i) {
      if (traffic_lights[i]->read() == GREEN) {
        if (--counters[i] <= 0) {
          car_signals[i]->write(false);
        }
      } else {
        int value{rand() % 100};
        if (value < this->rate) {
          counters[i] = rand() % this->max_cars + 1;
          car_signals[i]->write(true);
        }
      }
    }
  }
}
