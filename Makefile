CC ?= gcc
CFLAGS ?= -Wall \
    -D_FORTIFY_SOURCE=2 \
    -Wextra -Wcast-align -Wcast-qual -Wpointer-arith \
    -Waggregate-return -Wunreachable-code -Wfloat-equal \
    -Wformat=2 -Wredundant-decls -Wundef \
    -Wdisabled-optimization -Wshadow -Wmissing-braces \
    -Wstrict-aliasing=2 -Wstrict-overflow=5 -Wconversion \
    -Wno-unused-parameter \
    -pedantic -std=c11

SOURCES=main.c data.c util.c
OBJECTS=$(SOURCES:.c=.o)
EXECUTABLE=testc

all: $(EXECUTABLE)


$(EXECUTABLE): $(OBJECTS)
	$(CC) $^ -o $@

%.o: %.c
	$(CC) -c $< $(CFLAGS)

clean:
	rm *.o $(EXECUTABLE)

.PHONY: clean
