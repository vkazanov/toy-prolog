#ifndef UNIFY_H
#define UNIFY_H
#include <stdbool.h>
#include "data.h"

bool unify(Term* srcTerm, Env* srcEnv, Term* destTerm, Env* destEnv);

#endif //UNIFY_H
