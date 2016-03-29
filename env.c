#include <stdio.h>
#include <string.h>
#include "env.h"

void env_init(Env* env) {
    env->count = 0;
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

bool env_set(Env* env, char* key, char* value) {
    size_t count = env->count;
    env->keys[count] = key;
    env->values[count] = value;
    env->count++;
    return true;
}

bool env_has(Env* env, const char* key) {
    return env_get(env, key) != NULL;
}
