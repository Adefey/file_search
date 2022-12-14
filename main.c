#include "vector.h"
#include <dirent.h>
#include <fnmatch.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

int filter(const struct dirent *name) {
  if ((strcmp(name->d_name, ".") != 0) && (strcmp(name->d_name, "..") != 0)) {
    return 1;
  }
  return 0;
}

void _get_file_paths(char *directory, char *wildcard, struct vector *v) {
  char *dir_path = malloc(PATH_MAX * sizeof(char));
  realpath(directory, dir_path);
  struct dirent **entries = NULL;
  int _fetched_count = 0;
  _fetched_count =
      scandir(dir_path, &entries, filter,
              alphasort); // not found or error == -1; size_t brakes on -1
  size_t fetched_count = (size_t)_fetched_count;
  if (_fetched_count != -1) {
    for (size_t i = 0; i < fetched_count; ++i) {
      char *full_filename =
          malloc((strlen(dir_path) + strlen(entries[i]->d_name) + 2) *
                 sizeof(char)); //+2 == strlen("/") + new /0
      full_filename[0] = 0;
      strcat(full_filename, dir_path);
      strcat(full_filename, "/");
      strcat(full_filename, entries[i]->d_name);
      switch (entries[i]->d_type) {
      case DT_REG:
        if (!fnmatch(wildcard, entries[i]->d_name, FNM_NOESCAPE)) {
          vector_push_ptr_back(v, full_filename,
                               strlen(full_filename) +
                                   1); // strlen does not count /0
        }
        break;
      case DT_DIR:
        _get_file_paths(full_filename, wildcard, v);
        break;
      }
      free(full_filename);
    }
    for (size_t i = 0; i < fetched_count; ++i) {
      free(entries[i]);
    }
    free(entries);
  }
  free(dir_path);
}

int get_file_paths(char *directory, char *wildcard, struct vector *v) {
  _get_file_paths(directory, wildcard, v);

  return vector_size(v);
}

int main(int argc, char **argv) {
  if (argc != 3) {
    printf("%s%d\n",
           "Usage: ./executable path wildcard;\nGiven arguments count: ", argc);
    return EXIT_FAILURE;
  }

  struct vector *v = NULL;
  vector_create(&v);

  size_t size = get_file_paths(argv[1], argv[2], v);

  for (size_t i = 0; i < size; ++i) {
    printf("%s%c", vector_get_ptr_at(v, i), '\n');
  }

  vector_destroy(&v);

  return EXIT_SUCCESS;
}
