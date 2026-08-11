#include "sad.h"

// The original (unoptimized) implementation of SAD
int compute_sad_original (
  uint8_t A[IMAGE_HEIGHT][IMAGE_WIDTH], 
  uint8_t B[IMAGE_HEIGHT][IMAGE_WIDTH], 
  int x, 
  int y, 
  int r, 
  int s
) {
  int diff, sad = 0;
  int i, j;

  for (i=0; i<BLOCK_SIZE; i++) {
    for ( j=0; j<BLOCK_SIZE; j++) {
      diff = A[x+i][y+j] - B[(x+r)+i][(y+s)+j];
      
      if (diff < 0) {
        sad -= diff;
      }
      else {
        sad += diff;
      }
    }
  }

  return sad;
}

// The new (optimized) implementation of SAD
int compute_sad_new (
  uint8_t A[IMAGE_HEIGHT][IMAGE_WIDTH], 
  uint8_t B[IMAGE_HEIGHT][IMAGE_WIDTH], 
  int x, 
  int y, 
  int r, 
  int s
) {
  int sad = 0;
  int i;

  for (i=0; i<BLOCK_SIZE; i++) {
    uint8_t const *a = &A[x+i][y];
    uint8_t const *b = &B[(x+r)+i][(y+s)];

    // Perform one load of 16 uint8_t from memory into each NEON vector
    uint8x16_t vector_a = vld1q_u8(a); 
    uint8x16_t vector_b = vld1q_u8(b);

    // Perform subtraction and absolute-value operation
    uint8x16_t diff = vabdq_u8(vector_a, vector_b);

    // Reduction
    uint16x8_t temp1 = vpaddlq_u8(diff);                                     // Adds pairs of adjacent values
    uint16x4_t temp2 = vpadd_u16(vget_low_u16(temp1), vget_high_u16(temp1)); // Concatenates the two vectors then adds pairs of adjacent values
    temp2 = vpadd_u16(temp2, temp2);
    temp2 = vpadd_u16(temp2, temp2);
    sad += vget_lane_u16(temp2, 0);
  }

  return sad;
}

// An implementation of SAD using only vectorization
int compute_sad_vectorization (
  uint8_t A[IMAGE_HEIGHT][IMAGE_WIDTH], 
  uint8_t B[IMAGE_HEIGHT][IMAGE_WIDTH], 
  int x, 
  int y, 
  int r, 
  int s
) {
  int i;
  uint16x8_t sum = vdupq_n_u16(0); // Eight 16-bit lanes hold running pairwise sums across all rows

  for (i=0; i<BLOCK_SIZE; i++) {
    uint8_t const *a = &A[x+i][y];
    uint8_t const *b = &B[(x+r)+i][(y+s)];

    // Perform one load of sixteen uint8_t from memory into each vector
    uint8x16_t vector_a = vld1q_u8(a); 
    uint8x16_t vector_b = vld1q_u8(b);

    // Perform subtraction and absolute-value operation
    uint8x16_t diff = vabdq_u8(vector_a, vector_b);

    // Reduce and accumulate
    uint16x8_t pair_sums = vpaddlq_u8(diff); // Pairwise add the adjacent 8-bit differences and widen each result to 16 bits
    sum = vaddq_u16(sum, pair_sums);
  }
  
  // Reduction (pairwise add the lower and upper halves)                              
  uint16x4_t temp = vpadd_u16(vget_low_u16(sum), vget_high_u16(sum));
  temp = vpadd_u16(temp, temp)
  temp = vpadd_u16(temp, temp);
  return vget_lane_u16(temp, 0);
}

// An implementation of SAD using only pipelining
int compute_sad_pipelining (
  uint8_t A[IMAGE_HEIGHT][IMAGE_WIDTH], 
  uint8_t B[IMAGE_HEIGHT][IMAGE_WIDTH], 
  int x, 
  int y, 
  int r, 
  int s
) {
  int diff, sad = 0;
  int i, j;

  for (i=0; i<BLOCK_SIZE; i++) {
    // Loop prologue
    diff = A[x+i][y+0] - B[(x+r)+i][(y+s)+0];
    
    for ( j=0; j<(BLOCK_SIZE-1); j++) {
      // Loop kernel
      if (diff < 0) {
        sad -= diff;
      }
      else {
        sad += diff;
      }
      diff = A[x+i][y+j+1] - B[(x+r)+i][(y+s)+j+1];
    }

    // Loop epilogue
    if (diff < 0) {
      sad -= diff;
    }
    else {
      sad += diff;
    }
  }

  return sad;
}
