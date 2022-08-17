#include "vector.h"

void create(struct vector **this) {
  *this = malloc(sizeof(struct vector));
  (*this)->content = NULL;
  (*this)->size = 0;
  (*this)->allocated = 0;
}

void _expand(struct vector *this) {
  this->allocated = (!this->allocated) ? 1 : this->allocated * 2;
  this->content = realloc(this->content, this->allocated * (sizeof(void *)));
}

void push_back(struct vector *this, void *value_ptr,
               size_t value_size) // adds value to vector with deep copy
{
  if ((this->allocated - this->size) < 2) {
    _expand(this);
  }
  this->content[this->size++] =
      malloc((value_size + 1) * sizeof(char)); //+1 for strings
  memcpy(this->content[this->size - 1], value_ptr,
         value_size + 1); //+1 for strings (null terminator)
}

void *get_at(struct vector *this, size_t ind) {
  if (ind < this->size) {
    return this->content[ind];
  }
  return NULL;
}

void set_at(struct vector *this, size_t ind, void *value_ptr,
            size_t value_size) {
  if (ind < this->size) {
    free(this->content[ind]);
    this->content[this->size++] = malloc((value_size + 1) * sizeof(char));
    memcpy(this->content[this->size], value_ptr, value_size + 1);
  }
}

void destroy(struct vector **this) // also destroys inside values
{
  for (size_t i = 0; i < (*this)->size; ++i) {
    free((*this)->content[i]);
  }
  free((*this)->content);
  free(*this);
}

size_t size(struct vector *this) { return this->size; }
