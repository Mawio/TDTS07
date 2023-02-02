#include <systemc.h>
#include "lights.h"
#include "input_gen_rand.h"
#include "monitor.h"
#include <vector>

#define ARG_COUNT 1
#define SIM_TIME 40

enum Orientation {
  SOUTH = 0,
  WEST = 1,
  NORTH = 2,
  EAST = 3,
};

int sc_main(int argc, char **argv)
{
  // 1. the simulation time (in seconds),

  // assert(argc == ARG_COUNT+1);

  // Create channels.
  sc_signal<bool> light_signals[4];
  sc_signal<bool> cars[4];

  // Instantiate modules.
  TrafficLight light_south{"LightSouth"};
  TrafficLight light_west{"LightWest"};
  TrafficLight light_north{"LightNorth"};
  TrafficLight light_east{"LightEast"};
  TrafficLight* traffic_lights[] { &light_south, &light_west, &light_north, &light_east };

  RandomGenerator gen{"RandomGenerator"};
  Monitor monitor{"Monitor"};

  for (size_t i{}; i < 4; ++i) {
    traffic_lights[i]->output(light_signals[i]);
    traffic_lights[i]->opposite(light_signals[(i+2)%4]);
    traffic_lights[i]->orthogonal_right(light_signals[(i+3)%4]);
    traffic_lights[i]->orthogonal_left(light_signals[(i+1)%4]);

    traffic_lights[i]->car_status(cars[i]);

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

