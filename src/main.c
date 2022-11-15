#include <stdlib.h>

#include "bitmap-buffer.h"
#include "image-io.h"
#include "ray-casting.h"

#include "program-arguments.h"

static error_t parse_option(int key, char *arg, struct argp_state *state) {
  struct program_arguments *arguments = state->input;

  switch (key) {
  case 'w':
    arguments->width = atoi(arg);
    break;
  case 'f':
    arguments->file = arg;
    break;
  case ARGP_KEY_ARG:
    argp_usage(state);
    break;
  case ARGP_KEY_END:
    break;
  default:
    return ARGP_ERR_UNKNOWN;
  }

  return 0;
}

int main(int argc, char **argv) {
  struct program_arguments arguments;

  arguments.width = 512;
  arguments.file = "/tmp/corpuscle.png";

  argp_parse(&argp, argc, argv, 0, 0, &arguments);
  assert(arguments.width <= 4096);

  const double aspect_ratio = (16.0 / 9.0);

  BitmapBuffer bitmap = {.width = arguments.width,
                         .height = arguments.width / aspect_ratio,
                         .number_of_pixels =
                             arguments.width * (arguments.width / aspect_ratio),
                         .components_per_pixel = 3,
                         .data = malloc(sizeof(double) * 4096 * 2304 * 3)};
  assert(bitmap.data);

  cast_rays(&bitmap, aspect_ratio);

  int able_to_write_image;
  able_to_write_image = write_image_to_disk(arguments.file, &bitmap);

  free(bitmap.data);

  return (able_to_write_image) ? EXIT_SUCCESS : EXIT_FAILURE;
}
