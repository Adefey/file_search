#include "vector.h"

void vector_create(struct vector **self) {
  *self = malloc(sizeof(struct vector));
  (*self)->content = NULL;
  (*self)->size = 0;
  (*self)->allocated = 0;
}

void _vector_expand(struct vector *self) {
  self->allocated = (!self->allocated) ? 1 : self->allocated * 2;
  self->content = realloc(self->content, self->allocated * (sizeof(void *)));
}

void vector_push_ptr_back(
    struct vector *self, void *value_ptr,
    size_t value_size) // adds value to vector with deep copy
{
  if ((self->allocated - self->size) < 2) {
    _vector_expand(self);
  }
  self->content[self->size++] =
      malloc((value_size) * sizeof(char)); //+1 for strings
  memcpy(self->content[self->size - 1], value_ptr, value_size);
}

void *vector_get_ptr_at(struct vector *self, size_t ind) {
  if (ind < self->size) {
    return self->content[ind];
  }
  return NULL;
}

void vector_set_ptr_at(struct vector *self, size_t ind, void *value_ptr,
                       size_t value_size) {
  if (ind < self->size) {
    free(self->content[ind]);
    self->content[ind] = malloc(value_size * sizeof(char));
    memcpy(self->content[ind], value_ptr, value_size);
  }
}

void vector_destroy(struct vector **self) // also destroys inside values
{
  for (size_t i = 0; i < (*self)->size; ++i) {
    free((*self)->content[i]);
  }
  free((*self)->content);
  free(*self);
}

size_t vector_size(struct vector *self) { return self->size; }
