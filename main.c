#include "testbench.h"
#include <stdint.h>

int main () {
  uint8_t current_frame[240][320]; // [number of rows = height][number of columns = width]
  uint8_t reference_frame[240][320];

  /* Need to load in images here */

  run_testbench(current_frame, reference_frame);
  
  return 0;
}
