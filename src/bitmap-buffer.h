#pragma once

#include <assert.h>
#include <stdint.h>

#include <stddef.h>

typedef struct BitmapBuffer {
  size_t number_of_pixels;
  size_t components_per_pixel;
  uint16_t width;
  uint16_t height;
  double *data;
} BitmapBuffer;
