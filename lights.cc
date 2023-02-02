#include "lights.h"

TrafficLight::TrafficLight(sc_module_name name) : sc_module{name} {

  SC_METHOD(light_logic_method);
  dont_initialize();
  sensitive << orthogonal_left << orthogonal_right << car_status;

}

void TrafficLight::light_logic_method() {

  if(!car_status->read()) {
    if(output->read() == GREEN) output->write(RED);
  } else {
    if(output->read() == RED) {
      if(orthogonal_left->read() == RED && orthogonal_right->read() == RED) {
	output->write(GREEN);
      }
    }
  }
}
