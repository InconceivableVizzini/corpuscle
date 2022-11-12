#pragma once

#include <math.h>

#ifndef __STDC_IEC_559__
#error Float must be 32 bits and double 64 bits
#endif

typedef union vec2_32 {
  struct {
    float x, y;
  };
  struct {
    float u, v;
  };
  struct {
    float width, height;
  };
  float elements[2];
} vec2_32;

typedef union vec2_64 {
  struct {
    double x, y;
  };
  struct {
    double u, v;
  };
  struct {
    double width, height;
  };
  double elements[2];
} vec2_64;

typedef union vec3_32 {
  struct {
    float x, y, z;
  };
  struct {
    float u, v, w;
  };
  float elements[3];
} vec3_32;

typedef union vec3_64 {
  struct {
    double x, y, z;
  };
  struct {
    double u, v, w;
  };
  double elements[3];
} vec3_64;

static inline vec3_64 vec3_64_add(const vec3_64 left_operand,
                                  const vec3_64 right_operand);
static inline vec3_64 vec3_64_subtract(const vec3_64 left_operand,
                                       const vec3_64 right_operand);
static inline vec3_64 vec3_64_scalar_multiply(const vec3_64 vector,
                                              const double scalar);
static inline vec3_64 vec3_64_scalar_divide(const vec3_64 vector,
                                            const double scalar);
static inline double vec3_64_magnitude(const vec3_64 vector);
static inline double vec3_64_magnitude_squared(const vec3_64 vector);
static inline vec3_64 vec3_64_normalize(const vec3_64 vector);

inline vec3_64 vec3_64_add(const vec3_64 left_operand,
                           const vec3_64 right_operand) {
  return (vec3_64){.x = left_operand.x + right_operand.x,
                   .y = left_operand.y + right_operand.y,
                   .z = left_operand.z + right_operand.z};
}

inline vec3_64 vec3_64_subtract(const vec3_64 left_operand,
                                const vec3_64 right_operand) {
  return (vec3_64){.x = left_operand.x - right_operand.x,
                   .y = left_operand.y - right_operand.y,
                   .z = left_operand.z - right_operand.z};
}

inline vec3_64 vec3_64_scalar_multiply(const vec3_64 vector,
                                       const double scalar) {
  return (vec3_64){
      .x = vector.x * scalar, .y = vector.y * scalar, .z = vector.z * scalar};
}

inline vec3_64 vec3_64_scalar_divide(const vec3_64 vector,
                                     const double scalar) {
  return vec3_64_scalar_multiply(vector, 1 / scalar);
}

inline double vec3_64_magnitude(const vec3_64 vector) {
  return sqrt(vec3_64_magnitude_squared(vector));
}

inline double vec3_64_magnitude_squared(const vec3_64 vector) {
  return vector.x * vector.x + vector.y * vector.y + vector.z * vector.z;
}

inline vec3_64 vec3_64_normalize(const vec3_64 vector) {
  return vec3_64_scalar_divide(vector, vec3_64_magnitude(vector));
}
