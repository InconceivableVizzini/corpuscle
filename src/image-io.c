#include "image-io.h"
#include <inttypes.h>

#define STB_IMAGE_WRITE_IMPLEMENTATION
unsigned char *stbi_zlib_compress(unsigned char *data, int data_len,
                                  int *out_len, int quality);
unsigned char *stbi_write_png_to_mem(const unsigned char *pixels,
                                     int stride_bytes, int x, int y, int n,
                                     int *out_len);
#include "stb_image_write.h"

#define set_png_pixel_from_bitmap(buffer_index, dst, src)                      \
  dst[buffer_index] = (uint8_t)(src[buffer_index] * 255.999);                  \
  dst[buffer_index + 1] = (uint8_t)(src[buffer_index + 1] * 255.999);          \
  dst[buffer_index + 2] = (uint8_t)(src[buffer_index + 2] * 255.999);

int write_image_to_disk(char *output_file_path, BitmapBuffer *bitmap) {
  stbi_write_png_compression_level = 0;
  stbi_flip_vertically_on_write(1);

  uint8_t *const png_image_pixels =
      malloc(bitmap->components_per_pixel * bitmap->number_of_pixels);

  for (size_t y = 0; y < bitmap->height; y++) {
    for (size_t x = 0; x < bitmap->width; x++) {
      int width_offset = x * bitmap->components_per_pixel;
      int height_offset = bitmap->width * bitmap->components_per_pixel * y;
      int buffer_index = height_offset + width_offset;

      set_png_pixel_from_bitmap(buffer_index, png_image_pixels, bitmap->data);
    }
  }

  const int write_result =
      stbi_write_png(output_file_path, bitmap->width, bitmap->height,
                     bitmap->components_per_pixel, png_image_pixels,
                     bitmap->components_per_pixel * bitmap->width);

  free(png_image_pixels);

  return write_result;
}
