/*
Test Images

Reference frame:
Object top-left corner at (105, 86)

Current frame:
Object top-left corner at (101, 84)

Expected motion vector is:
r = 4
s = 2

When the motion estimation search is implemented, the algorithm
should identify (r, s) = (4, 2) as the best match.
*/

#include <stdio.h>
#include <stdint.h>
#include "sad.h"

void run_testbench (
  uint8_t current_frame[240][320],
  uint8_t reference_frame[240][320]
) {
  int x, y = 0;
  int r, s = 0;

  int result_original = compute_sad_original(current_frame, reference_frame, x, y, r, s);
  printf("Original (Unoptimized) SAD: %d\n", result_original);
}
