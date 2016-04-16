#define _GNU_SOURCE
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>

#include "data.h"
#include "util.h"

void env_init(Env* env) {
    env->count = 0;
}

Env* env_new() {
    Env* env = malloc(sizeof(Env));
    env_init(env);
    return env;
}

Env* env_copy(Env* env_orig) {
    Env* env_copy = env_new();
    for (size_t i = 0; i < env_orig->count; i++) {
        char* key = env_orig->keys[i];
        char* value = env_orig->values[i];
        env_set(env_copy, strdup(key), strdup(value));
    }
    return env_copy;
}

void env_destroy(Env* env) {
    for (size_t i; i < env->count; i++) {
        free(env->keys[i]);
        free(env->values[i]);
    }
    free(env);
}

void env_print(Env* env) {
    printf("Env { ");
    for (size_t i = 0; i < env->count; i++) {
        printf("%s: %s", env->keys[i], env->values[i]);
        if (i+1 < env->count) {
            printf(", ");
        }
    }
    printf(" }");
}

char* env_get(Env* env, char* key) {
    for (size_t i = 0; i < env->count; i++) {
        if (strcmp(key, env->keys[i]) == 0) {
            return env->values[i];
        }
    }
    return NULL;
}

int env_set(Env* env, char* key, char* value) {
    size_t count = env->count;
    env->keys[count] = strdup(key);
    env->values[count] = strdup(value);
    env->count++;
    return 0;
}

bool env_has(Env* env, char* key) {
    return env_get(env, key) != NULL;
}

void rule_init(Rule* rule, char* str) {
    /* expect "term-:term;term;..." */

    char buf[MAX_LINE_LENGTH];
    char* tmp_str = strdup(str);
    rule->str = strdup(str);
    rule->goal_count = 0;

    /* Parse head */
    char* saveptr = NULL;
    char* head_str = strtok_r(tmp_str, ":-", &saveptr);
    if (head_str == NULL) {
        sprintf(buf, "Syntax error in rule: %s 0", str);
        fail(buf);
    }

    Term* term = term_new(head_str);
    rule->head = term;

    /* Get the goals string */
    char* goals_str = strtok_r(NULL, ":-", &saveptr);
    if (goals_str == NULL) {
        /* No goals for this rule */
        return;
    }

    /* Replace ), with ); to make it easier to just split */
    char* cur_str = goals_str;
    while ( (cur_str = strstr(cur_str, "),")) != NULL) {
        cur_str[1] = ';';
    }

    /* Parse the goals */
    char* goal_str = strtok_r(goals_str, ";", &saveptr);
    term = term_new(goal_str);
    rule->goals[rule->goal_count] = term;
    rule->goal_count++;
    for (;;) {
        goal_str = strtok_r(NULL, ";", &saveptr);
        if (goal_str == NULL) {
            break;
        }
        term = term_new(goal_str);
        rule->goals[rule->goal_count] = term;
        rule->goal_count++;
    }

    free(tmp_str);
}

Rule* rule_new(char* str) {
    Rule* rule = malloc(sizeof(Rule));
    rule_init(rule, str);
    return rule;
}

Rule* rule_copy(Rule* orig_rule) {
    Rule* new_rule = malloc(sizeof(Rule));
    new_rule->str = strdup(orig_rule->str);
    new_rule->head = term_copy(orig_rule->head);
    for (size_t i = 0; i < orig_rule->goal_count; i++) {
        new_rule->goals[i] = term_copy(orig_rule->goals[i]);
    }
    new_rule->goal_count = orig_rule->goal_count;
    return new_rule;
}

void rule_destroy(Rule* rule) {
    // TODO:
}

void rule_print(Rule* rule) {
    term_print(rule->head);
    printf(" :- ");
    for (size_t i = 0; i < rule->goal_count; i++) {
        term_print(rule->goals[i]);
        if (i + 1 < rule->goal_count) {
            printf(",");
        }
    }
}

void rule_setgoal(Rule* rule, Term* term) {
    rule->goal_count = 1;
    rule->goals[0] = term_copy(term);
    /* TODO: mem leak here, should probably free the data first */
}

void term_init(Term* term, char* str) {
    /* printf("term_init from \"%s\"\n", str); */
    /* expect x(y,z...) */
    char* str_copy = strdup(str);
    char buf[256];
    term->str = strdup(str);
    term->arg_count = 0;

    size_t strsize = strlen(str_copy);

    /* Should end with ) */
    if (str_copy[strsize - 1] != ')') {
        sprintf(buf, "Syntax error in term: %s 0", str_copy);
        fail(buf);
    }

    /* Should start with a predicate name ( */
    char* pred = strdup(strtok(str_copy, "("));
    if (pred == NULL) {
        sprintf(buf, "Syntax error in term: %s 1", str_copy);
        fail(buf);
    }
    term->pred = pred;

    /* Predicate args */
    char* args_str = strdup(strtok(NULL, "("));
    if (args_str == NULL) {
        sprintf(buf, "Syntax error in term: %s 2", str_copy);
        fail(buf);
    }

    /* No need for the str copy anymore */
    free(str_copy);

    /* Strip the rightmost paren */
    args_str[strlen(args_str)-1] = '\0';


    /* Split args */
    char* token = strtok(args_str, ",");
    if (token != NULL) {
        term->args[term->arg_count] = strdup(token);
        term->arg_count++;
        for (;;) {
            token = strtok(NULL, ",");
            if (token == NULL) {
                break;
            }
            term->args[term->arg_count] = strdup(token);
            term->arg_count++;
        }
    }

    free(args_str);
}

Term* term_new(char* str) {
    Term* term = malloc(sizeof(Term));
    term_init(term, str);
    return term;
}

Term* term_copy(Term* orig_term) {
    return term_new(orig_term->str);
}

void term_destroy(Term* term) {
    free(term->str);
    free(term->pred);
    for (size_t i = 0; i < term->arg_count; i ++) {
        free(term->args[i]);
    }
    free(term);
}

void term_print(Term* term) {
    printf("%s(", term->pred);
    for (size_t i = 0; i < term->arg_count; i++) {
        printf("%s", term->args[i]);
        if (i+1 != term->arg_count) {
            printf(",");
        }
    }
    printf(")");
}

size_t term_arg_count(Term* term) {
    return term->arg_count;
}

char* term_arg(Term* term, size_t i) {
    assert(term);
    assert(i < term->arg_count);
    return term->args[i];
}

char* term_pred(Term* term) {
    return term->pred;
}

void goal_init(Goal* goal, Rule* rule, Goal* parent, Env* env) {
    static size_t goal_id = 0;
    goal_id += 1;
    goal->id = goal_id;
    goal->rule = rule;
    goal->parent = parent;
    goal->inx = 0;
    if (env == NULL) {
        Env* new_env = env_new();
        goal->env = new_env;
    } else {
        goal->env = env_copy(env);
    }
}

void goal_print(Goal* goal) {
    printf("Goal %zu ", goal->id);
    rule_print(goal->rule);
    printf(" ");
    printf("inx=%zu ", goal->inx);
    env_print(goal->env);
}

Goal* goal_copy(Goal* orig_goal) {
    Goal* new_goal = malloc(sizeof(Goal));
    goal_init(new_goal, rule_copy(orig_goal->rule), NULL, orig_goal->env);
    new_goal->inx = orig_goal->inx;
    new_goal->env = env_copy(orig_goal->env);
    new_goal->parent = orig_goal->parent != NULL ? goal_copy(orig_goal->parent) : NULL;
    return new_goal;
}
