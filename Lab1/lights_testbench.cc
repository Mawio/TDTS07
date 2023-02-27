#include "input_gen_deterministic.h"
#include "input_gen_rand.h"
#include "intersection.h"
#include "monitor.h"
#include <systemc.h>
#include <vector>

#define ARGC_RANDOM 5
#define ARGC_DETERMINISTIC 4

int sc_main(int argc, char **argv) {
  double sim_time = std::stod(argv[1]);
  int timeout = std::stoi(argv[2]);

  // Used by random input generator
  int max_cars{};
  int rate{};

  // Used by deterministic input generator
  std::string filename{};

  // Decide if the simulation should be based on random or deterministic input
  // based on the amount of arguments passed to the program
  if (argc == ARGC_RANDOM) {
    max_cars = std::stoi(argv[3]);
    rate = std::stoi(argv[4]);
  } else {
    filename = std::string{argv[3]};
  }

  // Create the channels
  sc_signal<bool, SC_MANY_WRITERS> light_signals[4];
  sc_signal<bool> cars[4];

  // Instantiate the monitor and the intersection
  Monitor monitor{"Monitor", timeout};
  Intersection intersection{"Intersection", timeout};

  // Assign the signals to the ports of the modules
  for (size_t i{}; i < 4; ++i) {
    intersection.lights[i](light_signals[i]);
    intersection.lights_local[i] = light_signals[i].read();
    intersection.car_status[i](cars[i]);

    monitor.traffic_lights[i](light_signals[i]);
    monitor.car_status[i](cars[i]);
  }

  if (argc == ARGC_RANDOM) {
    RandomGenerator gen{"RandomGenerator", max_cars, rate};
    for (size_t i{}; i < 4; ++i) {
      gen.traffic_lights[i](light_signals[i]);
      gen.car_signals[i](cars[i]);
    }
  } else {
    DeterministicGenerator det_gen{"DeterministicGenerator",
                                   std::ifstream{filename}};
    for (size_t i{}; i < 4; ++i) {
      det_gen.traffic_lights[i](light_signals[i]);
      det_gen.car_signals[i](cars[i]);
    }
  }

  // Start the simulation.
  sc_time t{sim_time, SC_SEC};
  sc_start(t);
  return 0;
}
