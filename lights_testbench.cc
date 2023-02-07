#include "input_gen_rand.h"
#include "intersection.h"
#include "monitor.h"
#include <systemc.h>
#include <vector>

#define ARG_COUNT 1
#define SIM_TIME 40

enum Orientation {
  SOUTH = 0,
  WEST = 1,
  NORTH = 2,
  EAST = 3,
};

int sc_main(int argc, char **argv) {
  // 1. the simulation time (in seconds),

  // assert(argc == ARG_COUNT+1);

  // Create channels.
  sc_signal<bool, SC_MANY_WRITERS> light_signals[4];
  sc_signal<bool> cars[4];

  // Instantiate modules.
  RandomGenerator gen{"RandomGenerator"};
  Monitor monitor{"Monitor"};
  Intersection intersection{"Intersection"};

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
  sc_time t{SIM_TIME, SC_SEC};
  sc_start(t);
  return 0;
}
