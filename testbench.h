#include <stdio.h>
#include "sad.h"

void run_testbench (
  int current_frame[240][320],
  int reference_frame[240][320]
) {
  int x, y = 0;
  int r, s = 0;

  int result_original = compute_sad_original(current_frame, reference_frame, x, y, r, s);
  printf("Original (Unoptimized) SAD: %d\n", result_original);
}
