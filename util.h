#ifndef UTIL_H
#define UTIL_H
#include <stddef.h>

#define MAX_STACK_DEPTH 512
#define MAX_OBJECT_NUM 4096

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

typedef struct MemoryManager MemoryManager;

struct MemoryManager {
    void* objects[MAX_OBJECT_NUM];
    void (*destructors[MAX_OBJECT_NUM])(void*);
    size_t obj_count;
};

void mmanager_init(MemoryManager* mmanager);
MemoryManager* mmanager_new();
void mmanager_destroy(MemoryManager* mmanager);
void mmanager_add(MemoryManager* mmanager, void* obj, void (destructor)(void*));
void mmanager_destroyall(MemoryManager* mmanager);

void fail(const char* error);
void quit();
void trim(char* str);
void remove_comments(char* buf);
void strip_whitespace(char* buf);

#endif //UTIL_H
