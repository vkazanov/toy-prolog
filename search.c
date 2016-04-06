#include <stdio.h>
#include "search.h"

#define MAX_STACK_DEPTH 256

extern bool trace;

void search(Term* term, Rule* rules, size_t rule_count) {
    /* static size_t goalId; */
    /* goalId = 0; */
    if (trace == true) {
        puts("Search for:");
        term_print(term);
    }

    Goal* goal = malloc(sizeof(Goal));
    Rule* rule = malloc(sizeof(Rule));
    rule_init(rule, "got(goal):-x(y)");
    goal_init(goal, rule, NULL, NULL);
    rule_setgoal(rule, term);

    if (trace == true) {
        puts("Stack:");
        goal_print(goal);
    }

    /* Search start */
    Goal* stack[MAX_STACK_DEPTH];
    stack[0] = goal;
    size_t stack_depth = 1;

    while (stack_depth > 0) {
        /* TODO: the loop */
    }

    /* TODO: how to cleanup? */
}
