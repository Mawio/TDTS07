#include "intersection.h"

Intersection::Intersection(sc_module_name name, int timeout)
    : sc_module{name}, timeout{timeout} {

  SC_METHOD(logic_method);
  dont_initialize();
  for (size_t i{0}; i < 4; ++i) {
    sensitive << car_status[i];
  }
  sensitive << timeouted;

  SC_THREAD(timeout_thread);
}

void Intersection::logic_method() {

  for (size_t i{0}; i < 4; ++i) {
    // If timeouted
    if (lights_local[i] != lights[i]->read()) {
      lights[i]->write(lights_local[i]);
      continue;
    }

    if (car_status[i]->read()) {
      if (lights_local[i] == RED) {
        if (lights_local[(i + 1) % 4] == RED &&
            lights_local[(i + 3) % 4] == RED) {
          lights_local[i] = GREEN;
          lights[i]->write(GREEN);
        }
      }
    } else {
      if (lights_local[i] == GREEN) {
        lights[i]->write(RED);
        lights_local[i] = RED;
      }
    }
  }
}

void Intersection::timeout_thread() {
  bool did_timeout = false;
  for (;;) {
    wait(1, SC_SEC);

    if (did_timeout) {
      timeouted.notify();
      did_timeout = false;
    }

    for (size_t i = 0; i < 4; i++) {
      if (lights_local[i] == GREEN) {
        if (++timers[i] == this->timeout) {
          lights_local[i] = RED;
          did_timeout = true;

          if (lights_local[(i + 2) % 4] == GREEN) {
            lights_local[(i + 2) % 4] = RED;
          }

          timeouted.notify();
        }
      } else {
        timers[i] = 0;
      }
    }
  }
}
