#include <stdio.h>
#include "data.h"
#include "search.h"

bool trace = false;

int main() {
    Rule rules[256];
    size_t rule_count = 0;

    {
        puts("Basic unification. Should succeed!");

        char* data = "smart(boy)";
        rule_init(&rules[0], data);
        rule_count++;

        char* query = "smart(boy)";
        Term* term = malloc(sizeof(Term));
        term_init(term, query);
        search(term, &rules[0], rule_count);

        puts("Done!");
    }

    puts("");

    {
        puts("Variable unification. Should succeed with X == boy!");

        char* query = "smart(X)";
        Term* term = malloc(sizeof(Term));
        term_init(term, query);
        search(term, &rules[0], rule_count);

        puts("Done!");
    }

    puts("");

    {
        puts("Variable unification. Should fail!");

        char* query = "smart(girl)";
        Term* term = malloc(sizeof(Term));
        term_init(term, query);
        search(term, &rules[0], rule_count);

        puts("Done!");
    }

    return EXIT_SUCCESS;
}
