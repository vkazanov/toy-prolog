#ifndef UTIL_H
#define UTIL_H
#include <stddef.h>

#define MAX_STACK_DEPTH 512

typedef struct Stack Stack;

struct Stack {
    void* stack[MAX_STACK_DEPTH];
    size_t depth;
};

void stack_init(Stack* stack);
void stack_push(Stack* stack, void* data);
void* stack_pop(Stack* stack);
void* stack_peek(Stack* stack);
size_t stack_depth(Stack* stack);

void fail(const char* error);
void quit();
void trim(char* str);
void remove_comments(char* buf);
void strip_whitespace(char* buf);

#endif //UTIL_H
