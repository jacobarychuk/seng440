#include "sad.h"

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

int compute_sad_new (
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
      if (diff >= 0) {
        sad += diff;
      }
    }
  }

  return sad;
}
