#include <argp.h>

static struct argp_option options[] = {
    {"width", 'w', "WIDTH", 0, "Width of the output image", 0},
    {"file", 'f', "FILE", 0, "The file to write the output image to", 0},
    {0}};

struct program_arguments {
  uint16_t width;
  char *file;
};

static char args_documentation[] = "";

static char program_documentation[] = "";

static error_t parse_option(int key, char *arg, struct argp_state *state);

static struct argp argp = {
    options, parse_option, args_documentation, program_documentation, 0, 0, 0};
