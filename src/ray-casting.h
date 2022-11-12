#include "vec.h"

void cast_rays(BitmapBuffer *bitmap, double aspect_ratio);

void cast_rays(BitmapBuffer *bitmap, const double aspect_ratio) {
  const double viewport_height = 2.0;
  const double viewport_width = aspect_ratio * viewport_height;
  const double focal_length = 1.0;
  const vec3_64 origin = {.x = 0.0, .y = 0.0, .z = 0.0};
  const vec3_64 white = {.x = 1.0, .y = 1.0, .z = 1.0};
  const vec3_64 blue = {.x = 0.5, .y = 0.7, .z = 1.0};
  const vec3_64 depth_direction = {.x = 0.0, .y = 0.0, .z = focal_length};
  const vec3_64 horizontal_direction = {
      .x = viewport_width, .y = 0.0, .z = 0.0};
  const vec3_64 half_horizontal_direction =
      (vec3_64){.x = viewport_width / 2, .y = 0.0, .z = 0.0};
  const vec3_64 vertical_direction =
      (vec3_64){.x = 0.0, .y = viewport_height, .z = 0.0};
  const vec3_64 half_vertical_direction =
      (vec3_64){.x = 0.0, .y = viewport_height / 2, .z = 0.0};
  /* bottom left corner = origin - half_horizontal - half_vertical - depth */
  const vec3_64 lower_left_corner = vec3_64_subtract(
      vec3_64_subtract(vec3_64_subtract(origin, half_horizontal_direction),
                       half_vertical_direction),
      depth_direction);

  for (size_t y = 0; y < bitmap->height; y++) {
    const vec3_64 vertical_uv_component = vec3_64_scalar_multiply(
        vertical_direction, (double)y / (double)(bitmap->height - 1));

    for (size_t x = 0; x < bitmap->width; x++) {
      const vec3_64 horizontal_uv_component = vec3_64_scalar_multiply(
          horizontal_direction, (double)x / (double)(bitmap->width - 1));
      const vec3_64 uv_direction =
          vec3_64_add(horizontal_uv_component, vertical_uv_component);

      const vec3_64 ray_direction =
          vec3_64_add(lower_left_corner, uv_direction);
      const vec3_64 ray_direction_normal = vec3_64_normalize(ray_direction);

      const double blend_amount = 0.5 * (ray_direction_normal.y + 1.0);
      const vec3_64 blended_white =
          vec3_64_scalar_multiply(white, 1.0 - blend_amount);
      const vec3_64 blended_blue = vec3_64_scalar_multiply(blue, blend_amount);

      const vec3_64 ray_color = vec3_64_add(blended_white, blended_blue);

      const int width_offset = x * bitmap->components_per_pixel;
      const int height_offset =
          (bitmap->width * bitmap->components_per_pixel * y);

      const int buffer_index = height_offset + width_offset;
      bitmap->data[buffer_index] = ray_color.x;
      bitmap->data[buffer_index + 1] = ray_color.y;
      bitmap->data[buffer_index + 2] = ray_color.z;
    }
  }
}
