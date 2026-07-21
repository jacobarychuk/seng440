/*
Test Images

Reference frame:
Object top-left corner at (112, 93)

Current frame:
Object top-left corner at (108, 91)

Expected motion vector is:
r = 2
s = 4

When the motion estimation search is implemented, the algorithm
should identify (r, s) = (4, 2) as the best match.
*/

#include <stdio.h>
#include <stdint.h>
#include "sad.h"

void run_testbench (
  uint8_t current_frame[IMAGE_HEIGHT][IMAGE_WIDTH],
  uint8_t reference_frame[IMAGE_HEIGHT][IMAGE_WIDTH]
) {
  int x = 0;
  int y = 0;
  int r = 0;
  int s = 0;

  int result_original = compute_sad_original(current_frame, reference_frame, x, y, r, s);
  printf("Original (Unoptimized) SAD: %d\n", result_original);

  int result_new = compute_sad_new(current_frame, reference_frame, x, y, r, s);
  printf("New (Optimized) SAD: %d\n", result_new);
}
