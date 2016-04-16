#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "minunit.h"
#include "data.h"
#include "unify.h"

int tests_run = 0;
bool trace = false;

/* Case 1: unification should succeed on two identic Terms */
static char* test_identic () {
    Term* leftTerm = term_new("boy(bill)");
    Env* leftEnv = env_new();

    Term* rightTerm = term_new("boy(bill)");
    Env* rightEnv = env_new();

    mu_assert("Error, can't unify boy(bill) and boy(bill)",
              unify(leftTerm,leftEnv,rightTerm,rightEnv));
    return 0;
}

/* Case 2: unification should NOT succeed on two different Terms with no vars */
static char* test_different () {
    Term* leftTerm = term_new("boy(bill)");
    Env* leftEnv = env_new();

    Term* rightTerm = term_new( "boy(frank)");
    Env* rightEnv = env_new();

    mu_assert("Error, unification succeded for different constants in Terms",
              !unify(leftTerm,leftEnv,rightTerm,rightEnv));
    return 0;
}

/* Case 3: should unify setting X to 'frank' */
static char* test_single_var () {
    Term* leftTerm = term_new("boy(frank)");
    Env* leftEnv = env_new();

    Term* rightTerm = term_new("boy(X)");
    Env* rightEnv = env_new();

    mu_assert("Error, failed to unify",
              unify(leftTerm,leftEnv,rightTerm,rightEnv));
    mu_assert("Error, wrong variable value",
              strcmp(env_get(rightEnv, "X"), "frank") == 0);
    return 0;
}

/* Case 4: should unify setting X to 'frank' and comparing constants*/
static char* test_var_and_atom () {
    Term* leftTerm = term_new("boy(frank,dima)");
    Env* leftEnv = env_new();

    Term* rightTerm = term_new("boy(X,dima)");
    Env* rightEnv = env_new();

    mu_assert("Error, failed to unify",
              unify(leftTerm,leftEnv,rightTerm,rightEnv));
    mu_assert("Error, wrong variable value",
              strcmp(env_get(rightEnv, "X"), "frank") == 0);
    return 0;
}

static char* all_tests() {
    mu_run_test(test_identic);
    mu_run_test(test_different);
    mu_run_test(test_single_var);
    mu_run_test(test_var_and_atom);
    return 0;
}

int main() {
    char *result = all_tests();
    if (result != 0) {
        printf("%s\n", result);
    }
    else {
        printf("ALL TESTS PASSED\n");
    }
    printf("Tests run: %d\n", tests_run);

    return result != 0;
}
