#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "minunit.h"
#include "data.h"
#include "unify.h"

int tests_run = 0;

/* Case 1: unification should succeed on two identic Terms */
static char* test_identic () {
    Term* leftTerm = malloc(sizeof leftTerm);
    term_init(leftTerm, "boy(bill)");
    Env* leftEnv = malloc(sizeof leftEnv);
    env_init(leftEnv);

    Term* rightTerm = malloc(sizeof rightTerm);
    term_init(rightTerm, "boy(bill)");
    Env* rightEnv = malloc(sizeof rightEnv);
    env_init(rightEnv);

    mu_assert("Error, can't unify boy(bill) and boy(bill)",
              unify(leftTerm,leftEnv,rightTerm,rightEnv));
    return 0;
}

/* Case 2: unification should NOT succeed on two different Terms with no vars */
static char* test_different () {
    Term* leftTerm = malloc(sizeof leftTerm);
    term_init(leftTerm, "boy(bill)");
    Env* leftEnv = malloc(sizeof leftEnv);
    env_init(leftEnv);

    Term* rightTerm = malloc(sizeof rightTerm);
    term_init(rightTerm, "boy(frank)");
    Env* rightEnv = malloc(sizeof rightEnv);
    env_init(rightEnv);

    mu_assert("Error, unification succeded for different constants in Terms",
              !unify(leftTerm,leftEnv,rightTerm,rightEnv));
    return 0;
}

/* Case 3: should unify setting X to 'frank' */
static char* test_single_var () {
    Term* leftTerm = malloc(sizeof leftTerm);
    term_init(leftTerm, "boy(frank)");
    Env* leftEnv = malloc(sizeof leftEnv);
    env_init(leftEnv);

    Term* rightTerm = malloc(sizeof rightTerm);
    term_init(rightTerm, "boy(X)");
    Env* rightEnv = malloc(sizeof rightEnv);
    env_init(rightEnv);

    mu_assert("Error, failed to unify",
              unify(leftTerm,leftEnv,rightTerm,rightEnv));
    mu_assert("Error, wrong variable value",
              strcmp(env_get(rightEnv, "X"), "frank") == 0);
    return 0;
}

/* Case 4: should unify setting X to 'frank' and comparing constants*/
static char* test_var_and_atom () {
    Term* leftTerm = malloc(sizeof leftTerm);
    term_init(leftTerm, "boy(frank,dima)");
    Env* leftEnv = malloc(sizeof leftEnv);
    env_init(leftEnv);

    Term* rightTerm = malloc(sizeof rightTerm);
    term_init(rightTerm, "boy(X,dima)");
    Env* rightEnv = malloc(sizeof rightEnv);
    env_init(rightEnv);

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
