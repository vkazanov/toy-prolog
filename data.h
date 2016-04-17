#ifndef DATA_H
#define DATA_H
#include <stdlib.h>
#include <stdbool.h>

#define MAX_ENV_SIZE 256
#define MAX_LINE_LENGTH 512
#define MAX_RULE_GOALS 256
#define MAX_TERM_ARGS 256

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
    Term* goals[MAX_RULE_GOALS];
    size_t goal_count;
};

struct Term {
    char* str;
    char* pred;
    char* args[MAX_TERM_ARGS];
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
Env* env_new();
Env* env_copy(Env* env_orig);
void env_destroy(Env* env);

void env_print(Env* env);
char* env_get(Env* env, char* key);
int env_set(Env* env, char* key, char* value);
bool env_has(Env* env, char* key);

void rule_init(Rule* rule, char* str);
Rule* rule_new(char* str);
Rule* rule_copy(Rule* rule);
void rule_destroy(Rule* rule);

void rule_print(Rule* rule);
void rule_setgoal(Rule* rule, Term* term);

void term_init(Term* term, char* str);
Term* term_new(char* str);
Term* term_copy(Term* term);
void term_destroy(Term* term);

void term_print(Term* term);
size_t term_arg_count(Term* term);
char* term_arg(Term* term, size_t i);
char* term_pred(Term* term);

Goal* goal_new(Rule* rule, Goal* parent, Env* env);
void goal_init(Goal* goal, Rule* rule, Goal* parent, Env* env);
Goal* goal_copy(Goal* goal);
void goal_destroy(Goal* rule);

Goal* goal_parent(Goal* goal);
void goal_print(Goal* goal);

#endif //DATA_H
