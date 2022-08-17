#include "vector.h"
#include <dirent.h>
#include <fnmatch.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

/*
 TODO
 1. вектор по человечески +
 2. проблемы с доступом решить +
 */

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
                 sizeof(char)); //+2 == strlen("/") + new null terminator
      full_filename[0] = 0;
      strcat(full_filename, dir_path);
      strcat(full_filename, "/");
      strcat(full_filename, entries[i]->d_name);
      switch (entries[i]->d_type) {
      case DT_REG:
        if (!fnmatch(wildcard, entries[i]->d_name, FNM_NOESCAPE)) {
          push_back(v, full_filename, strlen(full_filename));
        }
        break;
      case DT_DIR:
        _get_file_paths(full_filename, wildcard, v);
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

  return size(v);
}

int main(int argc, char **argv) {
  if (argc != 3) {
    printf("%s : %d",
           "Usage: ./executable path wildcard; Given arguments count", argc);
    return EXIT_FAILURE;
  }

  struct vector *v = NULL;
  create(&v);

  size_t size = get_file_paths(argv[1], argv[2], v);

  for (size_t i = 0; i < size; ++i) {
    printf("%s%c", get_at(v, i), '\n');
  }

  destroy(&v);

  return EXIT_SUCCESS;
}
