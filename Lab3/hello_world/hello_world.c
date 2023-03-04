#include "appsupport.h"

void main1() {
  int i;

  start_metric();
  pr("Starting Hello World", 0, PR_CPU_ID | PR_STRING | PR_NEWL);
  for(i=0;i<5;i++) {
      pr("", i, PR_CPU_ID | PR_DEC | PR_NEWL);
  }

  dump_light_metric(PR_CPU_ID);

  stop_metric();
  stop_simulation();
}

