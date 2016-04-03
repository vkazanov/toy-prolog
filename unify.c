#include <string.h>
#include <assert.h>
#include "unify.h"
#include <stdio.h>

static bool is_variable(char* arg);

bool unify(Term* srcTerm, Env* srcEnv, Term* destTerm, Env* destEnv) {
    size_t nargs = term_arg_count(srcTerm);

    /* terms should have have equal arg numbers */
    if ((nargs) != term_arg_count(destTerm)) {
        return false;
    }

    /* terms should have equal predicate names */
    if (strcmp(term_pred(srcTerm), term_pred(destTerm)) != 0) {
        return false;
    }

    /* For every source Term arg see if it's possible to unify */
    for (size_t i = 0; i < nargs; i++) {
        char* srcArg = term_arg(srcTerm, i);
        char* destArg = term_arg(destTerm, i);
        char* srcVal;
        if (is_variable(srcArg)) {
            srcVal = env_get(srcEnv,srcArg);
        } else {
            srcVal = srcArg;
        }
        /* a defined var or a constant? */
        if (srcVal != NULL) {
            if (is_variable(destArg)) {
                char* destVal = env_get(destEnv, destArg);
                if (destVal == NULL) {
                    env_set(destEnv, destArg, srcVal);
                } else if (strcmp(destVal, srcVal) != 0) {
                    return false;
                }
            } else if (strcmp(destArg, srcVal) != 0) {
                return false;
            }
        }
    }
    return true;
}

static bool is_variable(char* arg) {
    assert(arg);
    return arg[0] >= 'A' && arg[0] <= 'Z';
}
