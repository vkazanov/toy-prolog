#include <stdlib.h>
#include "env.h"

typedef struct Rule Rule;
typedef struct Term Term;
typedef struct Goal Goal;

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

void rule_init(Rule* rule, char* str);
void rule_print(Rule* rule);
Rule* rule_copy(Rule* rule);

void term_init(Term* term, char* str);
void term_print(Term* term);
Term* term_copy(Term* term);

void goal_init(Goal* goal, Rule* rule, Goal* parent, Env* env);
void goal_print(Goal* goal);
Goal* goal_copy(Goal* goal);
