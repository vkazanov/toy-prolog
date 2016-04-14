#define _GNU_SOURCE
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <errno.h>
#include <string.h>
#include <regex.h>
#include <assert.h>

#include "util.h"
#include "data.h"
#include "search.h"

bool trace = false;

Rule rules[256];
size_t rule_count = 0;

void proc_file(FILE* stream, char* delim);

int main (int argc, char* argv[argc+1]) {
    for (int i = 1; i < argc; i++) {
        char* filename = argv[i];
        if (strcmp(filename, ".") == 0) {
            return EXIT_SUCCESS;
        }
        FILE* file = fopen(filename, "r");
        if (!file) {
            fail("Failed to open a file");
        }
        proc_file(file, "");
        fclose(file);
    }
    proc_file(stdin, "? ");
    return EXIT_SUCCESS;
}

void proc_file(FILE* stream, char* prompt) {
    while (true) {
        if (strlen(prompt) != 0) {
            printf("%s", prompt);
        }
        size_t bytes_to_read = 256;
        char* buf = malloc(bytes_to_read+1);
        getline(&buf, &bytes_to_read, stream);

        trim(buf);
        remove_comments(buf);
        strip_whitespace(buf);

        /* Nothing left, just continue to the next line */
        if (strcmp(buf, "") == 0) {
            free(buf);
            continue;
        }

        /* See what the command is */
        size_t buflen = strlen(buf);
        char punc = buf[buflen-1];
        if (punc == '.' || punc == '?') {
            buf[buflen-1] = '\0';
        } else {
            punc = '.';
        }

        /* Main choices */
        if (strcmp(buf, "trace=0") == 0) {
            trace = false;
        } else if (strcmp(buf, "trace=1") == 0) {
            trace = true;
        } else if (strcmp(buf, "quit") == 0) {
            quit();
        } else if (strcmp(buf, "dump") == 0) {
            for (size_t i = 0; i < rule_count; i++) {
                rule_print(&rules[i]);
                puts("");
            }
        } else if (punc == '?') {
            Term term;
            term_init(&term, buf);
            search(&term, rules, rule_count);
        } else {
            rule_init(&rules[rule_count], strdup(buf));
            rule_count++;
        }
        free(buf);
    }
}
