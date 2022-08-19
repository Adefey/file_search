#include <stdlib.h>
#include <string.h>

#ifndef VECTOR
#define VECTOR

struct vector {
  void **content;
  size_t size;
  size_t allocated;
};

void create(struct vector **self);

void push_back(struct vector *self, void *value,
               size_t value_size); // adds value to vector with deep copy

void *get_at(struct vector *self, size_t ind);

void set_at(struct vector *self, size_t ind, void *value_ptr,
            size_t value_size);

void destroy(struct vector **self);

size_t size(struct vector *self);

#endif
