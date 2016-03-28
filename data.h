#include <stdlib.h>

typedef struct Rule Rule;
typedef struct Term Term;

struct Rule {
    char* str;
    Term* head;
    Term* goals[256];
    size_t goal_count;
};


void rule_init(Rule* rule, char* str);
void rule_print(Rule* rule);

struct Term {
    char* str;
    char* pred;
    char* args[256];
    size_t arg_count;
};

void term_init(Term* term, char* str);
void term_print(Term* term);
