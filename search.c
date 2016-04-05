#include <stdio.h>
#include "search.h"

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
    /* TODO: build stack */
    /* TODO: loop */
}
