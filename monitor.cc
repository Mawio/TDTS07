#include "monitor.h"

Monitor::Monitor(sc_module_name name) : sc_module(name){

  SC_METHOD(check_traffic_lights_status);
  dont_initialize();
  for(size_t i{0}; i < 4; ++i) {
    sensitive << traffic_lights[i];
  }

  SC_METHOD(check_generated_inputs);
  dont_initialize();
  for(size_t i{0}; i < 4; ++i) {
    sensitive << car_status[i];
  }

}

void Monitor::check_traffic_lights_status() {

 os << "At time: " << sc_time_stamp() << std::endl;
 for(size_t i{0}; i < 4; ++i) {
   auto&& traffic_light{traffic_lights[i]};
   if(traffic_light->read() == GREEN) {
     assert(traffic_lights[(i+1)%4]->read() == RED);
     assert(traffic_lights[(i+3)%4]->read() == RED);
   }
   os << i << ": " << (traffic_light->read() ? "GREEN" : "RED") << ";" << (car_status[i]->read() ? "Cars here" : "No cars") << std::endl;
 }
}

void Monitor::check_generated_inputs() {
}
