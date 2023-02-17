#include "input_gen_rand.h"
#include "intersection.h"
#include "monitor.h"
#include <systemc.h>
#include <vector>

#define ARG_COUNT 4

int sc_main(int argc, char **argv) {

  assert(argc == ARG_COUNT+1);
  double sim_time = std::stod(argv[1]);
  int timeout = std::stoi(argv[2]);
  int max_cars = std::stoi(argv[3]);
  int rate = std::stoi(argv[4]);

  // Create channels.
  sc_signal<bool, SC_MANY_WRITERS> light_signals[4];
  sc_signal<bool> cars[4];

  // Instantiate modules.
  RandomGenerator gen{"RandomGenerator", max_cars, rate};
  Monitor monitor{"Monitor", timeout};
  Intersection intersection{"Intersection", timeout};

  for (size_t i{}; i < 4; ++i) {
    intersection.lights[i](light_signals[i]);
    intersection.lights_local[i]=light_signals[i].read();
    intersection.car_status[i](cars[i]);

    gen.traffic_lights[i](light_signals[i]);
    gen.car_signals[i](cars[i]);

    monitor.traffic_lights[i](light_signals[i]);
    monitor.car_status[i](cars[i]);
  }

  // Start the simulation.
  sc_time t{sim_time, SC_SEC};
  sc_start(t);
  return 0;
}
