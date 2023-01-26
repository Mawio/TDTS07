#include "input_gen_rand.h"
#include <stdlib.h>

RandomGenerator::RandomGenerator(sc_module_name name) : sc_module{name} {

  SC_THREAD(generator_thread);

  for(size_t i{0}; i < 4; ++i) {
    car_signals[i].initialize(false);
  }

}

void RandomGenerator::generator_thread() {

  for(;;) {
    wait(1, SC_SEC);
    for(size_t i{0}; i < 4; ++i) {
      if(traffic_lights[i]->read() == LightColour::GREEN) {
	bool value{rand() % 2};
	if(value) {
	  car_signals[i]->write(false); //maybe does not work with timing
	}
      } else {
	bool value{rand() % 2};
	if(value) {
	  car_signals[i]->write(true); //again
	}
      }
    }
  }

}
