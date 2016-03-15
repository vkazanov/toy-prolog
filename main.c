#define _GNU_SOURCE
#include <stdlib.h>
#include <stdio.h>

void process_file(FILE* stream, char* delim) {
    size_t bytes_to_read = 100;
    char* buf = malloc (bytes_to_read+1);
    while (getline(&buf, &bytes_to_read, stream) != -1) {
        puts (buf);
    }
    /* TODO:  */
    if (delim && delim[0] != '\0') {
        return;
    }
    return;
}

int main (int argc, char* argv[argc+1]) {
    for (int i = 1; i < argc; i++) {
        FILE* file = fopen (argv[i], "r");
        process_file (file, "");
    }
    process_file(stdin, "? ");
    return EXIT_SUCCESS;
}
