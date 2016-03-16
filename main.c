#define _GNU_SOURCE
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>

void fail(const char* error);
void process_file(FILE* stream, char* delim);

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
        process_file(file, "");
        fclose(file);
    }
    /* process_file(stdin, "? "); */
    return EXIT_SUCCESS;
}

void fail(const char* error) {
    perror(error);
    exit(EXIT_FAILURE);
}

void process_file(FILE* stream, char* delim) {
    puts("process");
    return;
    size_t bytes_to_read = 256;
    char* buf = malloc(bytes_to_read+1);
    puts(delim);
    while (getline(&buf, &bytes_to_read, stream) != -1) {
        strtok(buf, "\n");
        if (delim && delim[0] != '\0' && strcmp(delim, buf) == 0) {
            break;
        }
    }
    free(buf);
}
