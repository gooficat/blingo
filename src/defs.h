#pragma once
#include <stddef.h>
#include <stdlib.h>

#define CLASS(name)                                                            \
  typedef struct name name;                                                    \
  struct name

#define ENUM(name, ...) typedef enum name __VA_ARGS__ name

#define VECTOR_TYPE(type)                                                      \
  CLASS(vector_##type) {                                                       \
    type *data;                                                                \
    size_t size;                                                               \
    size_t capacity;                                                           \
  }

#define MAKE_VECTOR(type)                                                      \
  (vector_##type){.data = malloc(sizeof(type)), .size = 0, .capacity = 1}

#define PUSH(vec, val)                                                         \
  {                                                                            \
    if ((vec).size > (vec).capacity) {                                         \
      (vec).capacity *= 2;                                                     \
      (vec).data = realloc((vec).data, (vec).capacity * sizeof(val));          \
    }                                                                          \
    (vec).data[(vec).size++] = val;                                            \
  }
#define at(i) data[i]
#define POP(vec)                                                               \
  {                                                                            \
    --(vec).size;                                                              \
    if ((vec).capacity / 2 > (vec).size) {                                     \
      (vec).capacity /= 2;                                                     \
      (vec).data = realloc((vec).data, (vec).capacity * sizeof(val));          \
    }                                                                          \
  }

typedef char *STRING;
