#ifndef DATA_H
#define DATA_H
#include <stdlib.h>
#include <stdbool.h>

#define MAX_ENV_SIZE 256

typedef struct Env Env;
typedef struct Rule Rule;
typedef struct Term Term;
typedef struct Goal Goal;

struct Env {
    char* keys[MAX_ENV_SIZE];
    char* values[MAX_ENV_SIZE];
    size_t count;
};

struct Rule {
    char* str;
    Term* head;
    Term* goals[256];
    size_t goal_count;
};

struct Term {
    char* str;
    char* pred;
    char* args[256];
    size_t arg_count;
};

struct Goal {
    size_t id;
    Rule* rule;

    Goal* parent;
    Env* env;

    size_t inx;
};

void env_init(Env* env);
void env_print(Env* env);
char* env_get(Env* env, char* key);
int env_set(Env* env, char* key, char* value);
bool env_has(Env* env, char* key);
Env* env_copy(Env* env_orig);

void rule_init(Rule* rule, char* str);
void rule_print(Rule* rule);
Rule* rule_copy(Rule* rule);
void rule_setgoal(Rule* rule, Term* term);

void term_init(Term* term, char* str);
void term_print(Term* term);
Term* term_copy(Term* term);
size_t term_arg_count(Term* term);
char* term_arg(Term* term, size_t i);
char* term_pred(Term* term);

void goal_init(Goal* goal, Rule* rule, Goal* parent, Env* env);
void goal_print(Goal* goal);
Goal* goal_copy(Goal* goal);

#endif //DATA_H
