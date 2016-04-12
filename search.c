#include <stdio.h>
#include <string.h>
#include "search.h"
#include "unify.h"

#define MAX_STACK_DEPTH 256

extern bool trace;

void search(Term* term, Rule* rules, size_t rule_count) {
    if (trace == true) {
        printf("Search ");
        term_print(term);
        puts("");
    }

    Rule* rule = malloc(sizeof(Rule));
    rule_init(rule, "got(goal):-x(y)");
    rule_setgoal(rule, term);

    Goal* goal = malloc(sizeof(Goal));
    goal_init(goal, rule, NULL, NULL);

    if (trace == true) {
        printf("Stack ");
        goal_print(goal);
        puts("");
    }

    /* Search start */
    Goal* stack[MAX_STACK_DEPTH] = { NULL };
    size_t stack_depth = 0;

    stack[stack_depth] = goal;
    stack_depth++;

    while (stack_depth > 0) {
        Goal* c = stack[stack_depth-1];
        stack_depth--;

        if (trace == true) {
            printf("  pop ");
            goal_print(c);
            puts("");
        }

        /* Last goal in the rule? */
        if (c->inx >= c->rule->goal_count) {
            /* Original goal? */
            if (c->parent == NULL) {
                /* We have a solution */
                if (c->env->count > 0) {
                    env_print(c->env);
                    puts("");
                } else {
                    puts("Yes");
                }
                continue;
            }

            Goal* parent = goal_copy(c->parent);
            unify(c->rule->head, c->env,
                  parent->rule->goals[parent->inx], parent->env);
            parent->inx++;

            if (trace == true) {
                printf("stack ");
                goal_print(parent);
                puts("");
            }

            stack[stack_depth] = parent;
            stack_depth++;
            continue;
        }

        /* Not yet finished with the goal. */
        term = c->rule->goals[c->inx];
        for (size_t i = 0; i < rule_count; i++) {
            rule = &rules[i];
            if (strcmp(rule->head->pred, term->pred) != 0) {
                continue;
            }
            if (rule->head->arg_count != term->arg_count) {
                continue;
            }

            Goal* child = malloc(sizeof(Goal));
            goal_init(child, rule, c, NULL);

            if (unify(term, c->env, rule->head, child->env) == true) {
                if (trace == true) {
                    printf("stack ");
                    goal_print(child);
                    puts("");
                }
                stack[stack_depth] = child;
                stack_depth++;
            }
        }
    }
}
