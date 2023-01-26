#include "lights.h"

TrafficLights::TrafficLight(sc_module_name name, LightColour colour) : sc_module{name} {

  output.initialize(colour);

  SC_METHOD(orthogonal_changed_method);
  dont_initialize();
  sensitive << orthogonal_left << orthogonal_right;

  SC_METHOD(car_status_changed_method);
  dont_initialize();
  sensitive << car_status;

}

void TrafficLights::orthogonal_changed_method() {

  if(!car_status->read()) {
    return;
  }

  if(orthogonal_left->read() == RED && orthogonal_right->read() == RED) {
    output->write(LightColour::GREEN); //may not work: this only changes next "turn", maybe consider making it change immediately or other solutions
  }

}

void TrafficLights::car_status_changed_method() {

  if(car_status->read()) {
    if(orthogonal_left->read() == RED && orthogonal_right->read() == RED) {
      output->write(LightColour::GREEN); //may not work: this only changes next "turn", maybe consider making it change immediately or other solutions
    }
  } else {
    output->write(LightColour::RED);
  }

}
