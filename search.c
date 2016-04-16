#include <stdio.h>
#include <string.h>
#include "search.h"
#include "unify.h"
#include "util.h"
#include "data.h"

extern bool trace;

void search(Term* term, Rule* rules, size_t rule_count) {
    if (trace == true) {
        printf("Search ");
        term_print(term);
        puts("");
    }

    Rule* rule = rule_new("got(goal):-x(y)");
    rule_setgoal(rule, term);

    Goal* goal = malloc(sizeof(Goal));
    goal_init(goal, rule, NULL, NULL);

    if (trace == true) {
        printf("Stack ");
        goal_print(goal);
        puts("");
    }

    /* Search start */
    Stack* stack = malloc(sizeof(Stack));
    stack_init(stack);
    stack_push(stack, goal);

    while (stack_depth(stack) > 0) {
        Goal* c = stack_pop(stack);

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

            stack_push(stack, parent);
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
                stack_push(stack, child);
            }
        }
    }

    free(stack);
}
