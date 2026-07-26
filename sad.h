#ifndef SAD_H
#define SAD_H

#include <stdint.h>
#include <arm_neon.h>

#define IMAGE_WIDTH 320
#define IMAGE_HEIGHT 240
#define BLOCK_SIZE 16

// The original (unoptimized) implementation of SAD
int compute_sad_original (
  uint8_t A[IMAGE_HEIGHT][IMAGE_WIDTH], 
  uint8_t B[IMAGE_HEIGHT][IMAGE_WIDTH], 
  int x, 
  int y, 
  int r, 
  int s
);

// The new (optimized) implementation of SAD
int compute_sad_new (
  uint8_t A[IMAGE_HEIGHT][IMAGE_WIDTH], 
  uint8_t B[IMAGE_HEIGHT][IMAGE_WIDTH], 
  int x, 
  int y, 
  int r, 
  int s
);

// An implementation of SAD using only vectorization
int compute_sad_vectorization (
  uint8_t A[IMAGE_HEIGHT][IMAGE_WIDTH], 
  uint8_t B[IMAGE_HEIGHT][IMAGE_WIDTH], 
  int x, 
  int y, 
  int r, 
  int s
);

#endif
