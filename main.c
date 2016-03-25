#define _GNU_SOURCE
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <errno.h>
#include <string.h>
#include <regex.h>

bool trace = false;

struct Rule {
    char* descr;
};
typedef struct Rule Rule;

Rule rules[256];
size_t rule_count = 0;

void rule_init(Rule* rule, char* descr);
void rule_print(Rule* rule);

void fail(const char* error);
void quit();
void proc_file(FILE* stream, char* delim);
void trim(char* str);
void remove_comments(char* buf);
void strip_whitespace(char* buf);

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

void fail(const char* error) {
    perror(error);
    exit(EXIT_FAILURE);
}

void quit() {
    exit(EXIT_SUCCESS);
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

        /* Empty line? stop */
        if (strcmp(buf, "") == 0) {
            free(buf);
            break;
        }

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
            }
        } else if (punc == '?') {
            /* TODO: Term*/
        } else {
            rule_init(&rules[rule_count], strdup(buf));
            rule_count++;
        }

        /* TODO: trace/quit */
        /* TODO: rules dump */
        /* TODO: rule add */
        /* TODO: search */

        free(buf);
    }
}

void trim(char* str) {
    char *pos = strchr(str, '\n');
    if (pos) {
        *pos = '\0';
    }
}

void strip_whitespace(char* buf) {
    char* i = buf;
    char* j = buf;
    while (*j != '\0') {
        *i = *j;
        j++;
        if (*i != ' ') {
            i++;
        }
    }
    *i = 0;
}

void remove_comments(char* buf) {
    regex_t regex;
    if (regcomp(&regex, "#.*", 0) != 0) {
        regfree(&regex);
        fail("Failed to compile a regular expression");
    }
    regmatch_t regmatch[1];
    if (regexec(&regex, buf, 1, regmatch, 0) == 0) {
        buf[regmatch[0].rm_so] = '\0';
    }
}

void rule_init(Rule* rule, char* descr) {
    rule->descr = descr;
}

void rule_print(Rule* rule) {
    printf("Rule: descr = %s\n", rule->descr);
}
