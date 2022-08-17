#include <stdlib.h>
#include <string.h>

#ifndef VECTOR
#define VECTOR

struct vector {
  void **content;
  size_t size;
  size_t allocated;
};

void create(struct vector **this);

void push_back(struct vector *this, void *value,
               size_t value_size); // adds value to vector with deep copy

void *get_at(struct vector *this, size_t ind);

void set_at(struct vector *this, size_t ind, void *value_ptr,
            size_t value_size);

void destroy(struct vector *this);

size_t size(struct vector *this);
#endif
