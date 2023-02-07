#include "intersection.h"

Intersection::Intersection(sc_module_name name) : sc_module{name} {

  SC_METHOD(logic_method);
  dont_initialize();
  for(size_t i{0}; i < 4; ++i) {
//lights_local[i] = lights[i]->read();
      sensitive << car_status[i];
  }

  SC_THREAD(timeout_thread);
}

void Intersection::logic_method() {

    for(size_t i{0}; i < 4; ++i) {
        if(car_status[i]->read()) {
            bool timeouted = timers[i] == 0;
            if(lights_local[i] == RED && !timeouted) {
                if(lights_local[(i+1)%4] == RED && lights_local[(i+3)%4] == RED) {
                    lights[i]->write(GREEN);
                    lights_local[i] = GREEN;
                    timers[i] = 1;
                }
            }
        } else {
            if(lights_local[i] == GREEN) {
                lights[i]->write(RED);
                lights_local[i] = RED;
            }
        }
    }
}

void Intersection::timeout_thread() {
    for (;;) {
        wait(1, SC_SEC);
        for (size_t i = 0; i < 4; i++) {
            if (--timers[i] == 0) {
                if (lights_local[i] == GREEN) {
                    lights_local[i] = RED;
                    lights[i]->write(RED);
                }
                if (lights_local[(i+2)%4] == GREEN) {
                    lights_local[(i+2)%4] = RED;
                    lights[(i+2)%4]->write(RED);
                }
            }
        }
    }
}
