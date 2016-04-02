#ifndef ENV_H
#define ENV_H
#include <stdbool.h>
#include <stdlib.h>

#define MAX_ENV_SIZE 256

typedef struct Env Env;

struct Env {
    char* keys[MAX_ENV_SIZE];
    char* values[MAX_ENV_SIZE];
    size_t count;
};

int env_init(Env* env);
void env_print(Env* env);
char* env_get(Env* env, const char* key);
int env_set(Env* env, char* key, char* value);
bool env_has(Env* env, const char* key);
Env* env_copy(const Env* env_orig);

#endif //ENV_H
