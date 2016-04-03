#include <string.h>
#include "unify.h"

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
    return false;
}
