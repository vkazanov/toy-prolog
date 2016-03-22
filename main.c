#define _GNU_SOURCE
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <errno.h>
#include <string.h>
#include <regex.h>

void fail(const char* error);
void procfile(FILE* stream, char* delim);
void trim(char* str);
void stripWhitespace(char* buf);

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
        procfile(file, "");
        fclose(file);
    }
    procfile(stdin, "? ");
    return EXIT_SUCCESS;
}

void fail(const char* error) {
    perror(error);
    exit(EXIT_FAILURE);
}

void procfile(FILE* stream, char* prompt) {
    while (true) {
        if (strlen(prompt) != 0) {
            printf("%s", prompt);
        }
        size_t bytes_to_read = 256;
        char* buf = malloc(bytes_to_read+1);
        getline(&buf, &bytes_to_read, stream);
        trim(buf);
        if (strcmp(buf, "") == 0) {
            free(buf);
            break;
        }

        /* Clip comments */
        regex_t regex;
        if (regcomp(&regex, "#.*", 0) != 0) {
            regfree(&regex);
            fail("Failed to compile a regular expression");
        }
        regmatch_t regmatch[1];
        if (regexec(&regex, buf, 1, regmatch, 0) == 0) {
            buf[regmatch[0].rm_so] = '\0';
        }

        /* Strip whitespaces */
        stripWhitespace(buf);

        /* nothing left, just continue to the next line */
        if (strcmp(buf, "") == 0) {
            free(buf);
            continue;
        }

        /* TODO: punc */
        /* TODO: trace/quit */
        /* TODO: rules dump */
        /* TODO: rule add */
        /* TODO: search */

        puts("results:");
        puts(buf);

        free(buf);
    }
}

void trim(char* str) {
    char *pos = strchr(str, '\n');
    if (pos) {
        *pos = '\0';
    }
}

void stripWhitespace(char* buf) {
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
