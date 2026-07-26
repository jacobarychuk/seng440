#include <stdint.h>
#include <stdio.h>
#include "sad.h"

int load_image (
  const char* filename,
  uint8_t image[IMAGE_HEIGHT][IMAGE_WIDTH] // [number of rows = height][number of columns = width]
) {
  FILE* fp = fopen(filename, "rb");

  if (fp == NULL)
    return 0; // Failure
  
  fread(image, sizeof(uint8_t), IMAGE_WIDTH*IMAGE_HEIGHT, fp);
  fclose(fp);

  return 1; // Success
}

int main () {
  uint8_t current_frame[IMAGE_HEIGHT][IMAGE_WIDTH];
  uint8_t reference_frame[IMAGE_HEIGHT][IMAGE_WIDTH];

  /* Need to load in images here */
  if (!load_image("current_frame.raw", current_frame)) {
    printf("Failed to load image: current_frame.raw\n");
    return 1;
  }

  if (!load_image("reference_frame.raw", reference_frame)) {
    printf("Failed to load image: reference_frame.raw\n");
    return 1;
  }

  int x = 91;
  int y = 108;
  int r = 1;
  int s = 3;
  int sad_original = compute_sad_original(current_frame, reference_frame, x, y, r, s);
  int sad_new = compute_sad_new(current_frame, reference_frame, x, y, r, s);
  int sad_vectorization = compute_sad_vectorization(current_frame, reference_frame, x, y, r, s);
  
  return 0;
}
