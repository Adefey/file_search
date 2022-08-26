#include <stdlib.h>
#include <string.h>

#ifndef VECTOR
#define VECTOR

struct vector {
  void **content;
  size_t size;
  size_t allocated;
};

void vector_create(struct vector **self);

void vector_push_ptr_back(
    struct vector *self, void *value,
    size_t value_size); // adds value to vector with deep copy

#define vector_push_back(self, value, type)                                    \
  {                                                                            \
    {                                                                          \
      type *buf = (type *)malloc(sizeof(type));                                \
      *buf = value;                                                            \
      vector_push_ptr_back(self, buf, sizeof(type));                           \
      free(buf);                                                               \
    }                                                                          \
  }

void *vector_get_ptr_at(struct vector *self, size_t ind);

#define vector_get_at(self, ind, type) (*((type *)vector_get_ptr_at(self, ind)))

void vector_set_ptr_at(struct vector *self, size_t ind, void *value_ptr,
                       size_t value_size);

#define vector_set_at(self, ind, value, type)                                  \
  vector_set_ptr_at(self, ind, &value, sizeof(type))

#define vector_

void vector_destroy(struct vector **self);

size_t vector_size(struct vector *self);

#endif
