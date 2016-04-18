#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <regex.h>

#include "util.h"

void stack_init(Stack* stack) {
    stack->depth = 0;
}

void stack_push(Stack* stack, void* data) {
    stack->stack[stack->depth] = data;
    stack->depth++;
}

void* stack_pop(Stack* stack) {
    if (stack->depth < 1) {
        return NULL;
    }
    stack->depth--;
    return stack->stack[stack->depth];
}

void* stack_peek(Stack* stack) {
    if (stack->depth < 1) {
        return NULL;
    }
    return stack->stack[stack->depth-1];
}

size_t stack_depth(Stack* stack) {
    return stack->depth;
}

void mmanager_init(MemoryManager* mmanager) {
    mmanager->obj_count = 0;
}

MemoryManager* mmanager_new() {
    MemoryManager* mmanager = malloc(sizeof(MemoryManager));
    mmanager_init(mmanager);
    return mmanager;
}

void mmanager_destroy(MemoryManager* mmanager) {
    mmanager_destroyall(mmanager);
    free(mmanager);
}

void mmanager_add(MemoryManager* mmanager, void* obj, void (destructor)(void*)) {
    mmanager->destructors[mmanager->obj_count] = destructor;
    mmanager->objects[mmanager->obj_count] = obj;
    mmanager->obj_count++;
}

void mmanager_destroyall(MemoryManager* mmanager) {
    for (size_t i = 0; i < mmanager->obj_count; i++) {
        (mmanager->destructors[i])(mmanager->objects[i]);
    }
    mmanager->obj_count = 0;
}

void trim(char* str) {
    char *pos = strchr(str, '\n');
    if (pos) {
        *pos = '\0';
    }
}

void strip_whitespace(char* buf) {
    char* i = buf;
    char* j = buf;
    while (*j != '\0') {
        *i = *j;
        j++;
        if (*i != ' ') {
            i++;
        }
    }
    *i = 0;
}

void remove_comments(char* buf) {
    regex_t regex;
    if (regcomp(&regex, "#.*", 0) != 0) {
        regfree(&regex);
        fail("Failed to compile a regular expression");
    }
    regmatch_t regmatch[1];
    if (regexec(&regex, buf, 1, regmatch, 0) == 0) {
        buf[regmatch[0].rm_so] = '\0';
    }
    regfree(&regex);
}

void fail(const char* error) {
    perror(error);
    exit(EXIT_FAILURE);
}

void quit() {
    exit(EXIT_SUCCESS);
}
