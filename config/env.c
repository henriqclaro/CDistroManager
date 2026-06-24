#include "../include/config/env.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void set_env_var(const char *name, const char *value) {
#ifdef _WIN32
  _putenv_s(name, value);
#else
  setenv(name, value, 1);
#endif
}

void load_env() {
  FILE *file = fopen(".env", "r");

  if (file == NULL) {
    fprintf(stderr, "Warning: .env file not found");
    exit(1);
  }

  char line[256];

  while (fgets(line, sizeof(line), file)) {
    line[strcspn(line, "\r\n")] = 0;

    if (line[0] == 0 || line[0] == '#') {
      continue;
    }

    char *key = strtok(line, "=");
    char *value = strtok(NULL, "=");

    if (key && value) {
      set_env_var(key, value);
    }
  }

  fclose(file);
}