#include <stdio.h>
#include "data.h"
#include "search.h"

bool trace = true;

int main() {
    Rule rules[256];
    size_t rule_count = 0;

    {
        puts("Basic unification. Should succeed!");

        rule_init(&rules[0], "smart(boy)");
        rule_count = 1;

        Term* term = malloc(sizeof(Term));
        term_init(term, "smart(boy)");
        search(term, &rules[0], rule_count);

        puts("Done!");
    }

    puts("");

    {
        puts("Variable unification. Should succeed with X == boy!");

        rule_init(&rules[0], "smart(boy)");
        rule_count = 1;

        Term* term = malloc(sizeof(Term));
        term_init(term, "smart(X)");
        search(term, &rules[0], rule_count);

        puts("Done!");
    }

    puts("");

    {
        puts("Variable unification. Should fail!");

        Term* term = malloc(sizeof(Term));
        term_init(term, "smart(girl)");
        search(term, &rules[0], rule_count);

        puts("Done!");
    }

    puts("");

    {
        puts("A more involved search. Should succeed with 2 results");

        rule_init(&rules[0], "child(X):-boy(X)");
        rule_init(&rules[1], "child(X):-girl(X)");
        rule_init(&rules[2], "girl(alice)");
        rule_init(&rules[3], "boy(alex)");
        rule_count = 4;

        Term term;
        term_init(&term, "child(Q)");
        search(&term, rules, rule_count);

        puts("Done!");
    }

    return EXIT_SUCCESS;
}
