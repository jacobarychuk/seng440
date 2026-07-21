/*
Test Images

Reference frame:
Object top-left corner at (112, 93)

Current frame:
Object top-left corner at (108, 91)
*/

#include <stdio.h>
#include <stdint.h>
#include "limits.h"
#include "sad.h"

void run_testbench (
  uint8_t current_frame[IMAGE_HEIGHT][IMAGE_WIDTH],
  uint8_t reference_frame[IMAGE_HEIGHT][IMAGE_WIDTH]
) {
  // Block from current frame is fixed (chosen near top left of object in current frame)
  int x = 91;
  int y = 108;

  int best_sad_original = INT_MAX;
  int best_sad_new = INT_MAX;
  int best_r_original, best_s_original;
  int best_r_new, best_s_new;
  
  // Compare block from current frame to nearby blocks in the reference frame
  for (int r = -4; r <= 4; r++) {
    for (int s = -4; s <= 4; s++) {
      int sad_original = compute_sad_original(current_frame, reference_frame, x, y, r, s);
      if (sad_original < best_sad_original) {
        best_sad_original = sad_original;
        best_r_original = r;
        best_s_original = s;
      }
      
      int sad_new = compute_sad_new(current_frame, reference_frame, x, y, r, s);
      if (sad_new < best_sad_new) {
        best_sad_new = sad_new;
        best_r_new = r;
        best_s_new = s;
      }
    }
  }
  
  printf(
    "Original implementation: minimum SAD = %d at motion vector (r=%d, s=%d)\n",
    best_sad_original,
    best_r_original,
    best_s_original
  );
  printf(
    "Optimized implementation: minimum SAD = %d at motion vector (r=%d, s=%d)\n",
    best_sad_new,
    best_r_new,
    best_s_new
  );

  if (
    best_sad_original == best_sad_new &&
    best_r_original == best_r_new &&
    best_s_original == best_s_new
  ) {
    printf("\nPASS: The optimized implementation produced the same result as the original implementation.\n"); 
  } else {
    printf("\nFAIL: The optimized implementation produced a different result than the original implementation.\n");
  }
}
