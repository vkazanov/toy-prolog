#include <stdio.h>
#include "data.h"
#include "search.h"

bool trace = true;

int main() {
    Rule rules[256];
    size_t rule_count = 0;

    /* A primitive case */
    {
        puts("Basic unification. Should succeed!");

        char* data = "smart(boy)";
        rule_init(&rules[0], data);
        rule_count++;

        puts(data);
        puts("should unify with");
        char* query = "smart(boy)";
        puts(query);

        Term* term = malloc(sizeof(Term));
        term_init(term, query);
        search(term, &rules[0], rule_count);

        puts("Done!");
    }

    /* Variable unification */
    {
        puts("Variable unification. Should succeed with X == boy!");

        char* query = "smart(X)";
        puts(query);
        Term* term = malloc(sizeof(Term));
        term_init(term, query);
        search(term, &rules[0], rule_count);

        puts("Done!");
    }

    /* Fail to unify */
    {
        puts("Variable unification. Should fail!");

        char* query = "smart(girl)";
        puts(query);
        Term* term = malloc(sizeof(Term));
        term_init(term, query);
        search(term, &rules[0], rule_count);

        puts("Done!");
    }

    return EXIT_SUCCESS;
}
