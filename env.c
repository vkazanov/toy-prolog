#define _GNU_SOURCE
#include <stdio.h>
#include <string.h>
#include "env.h"

int env_init(Env* env) {
    env->count = 0;
    return 0;
}

void env_print(Env* env) {
    printf("Env { ");
    for (size_t i = 0; i < env->count; i++) {
        printf("%s: %s", env->keys[i], env->values[i]);
        if (i+1 < env->count) {
            printf(", ");
        }
    }
    printf(" }\n");
}

char* env_get(Env* env, const char* key) {
    for (size_t i = 0; i < env->count; i++) {
        if (strcmp(key, env->keys[i]) == 0) {
            return env->values[i];
        }
    }
    return NULL;
}

int env_set(Env* env, char* key, char* value) {
    size_t count = env->count;
    env->keys[count] = strdup(key);
    env->values[count] = strdup(value);
    env->count++;
    return 0;
}

bool env_has(Env* env, const char* key) {
    return env_get(env, key) != NULL;
}

Env* env_copy(const Env* env_orig) {
    Env* env_new = malloc(sizeof(env_new));
    env_init(env_new);
    for (size_t i = 0; i < env_orig->count; i++) {
        char* key = env_orig->keys[i];
        char* value = env_orig->values[i];
        env_set(env_new, strdup(key), strdup(value));
    }
    return env_new;
}
