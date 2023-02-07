#include "lights.h"

TrafficLight::TrafficLight(sc_module_name name) : sc_module{name} {

  SC_METHOD(light_logic_method);
  dont_initialize();
  //sensitive << orthogonal_left << orthogonal_right << car_status;

  SC_THREAD(light_logic_thread);
}

void TrafficLight::light_logic_method() {
  if (!car_status->read()) {
    if (output->read() == GREEN) {
      output->write(RED);
      wait(SC_ZERO_TIME);
    }
  } else {
    if (output->read() == RED) {
      if (orthogonal_left->read() == RED && orthogonal_right->read() == RED) {
        output->write(GREEN);
        wait(SC_ZERO_TIME);
      }
    }
  }
}

void TrafficLight::light_logic_thread() {

  for (;;) {
    wait(1);
    if (!car_status->read()) {
      if (output->read() == GREEN) {
        output->write(RED);
        wait(0);
      }
    } else {
      if (output->read() == RED) {
        if (orthogonal_left->read() == RED && orthogonal_right->read() == RED) {
          output->write(GREEN);
          wait(0);
        }
      }
    }
  }
}
