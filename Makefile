CC ?= gcc
CFLAGS ?= -Wall \
    -D_FORTIFY_SOURCE=2 \
    -Wextra -Wcast-align -Wcast-qual -Wpointer-arith \
    -Waggregate-return -Wunreachable-code -Wfloat-equal \
    -Wformat=2 -Wredundant-decls -Wundef \
    -Wdisabled-optimization -Wshadow -Wmissing-braces \
    -Wstrict-aliasing=2 -Wstrict-overflow=5 -Wconversion \
    -Wno-unused-parameter \
    -pedantic -std=c11 -g

SOURCES=data.c util.c env.c unify.c search.c
OBJECTS=$(SOURCES:.c=.o)
EXECUTABLE=testc

all: $(EXECUTABLE)

test: unify_test search_test
	./unify_test
	./search_test

search_test: search_test.o $(OBJECTS)
	$(CC) $^ -o $@

unify_test: unify_test.o $(OBJECTS)
	$(CC) $^ -o $@

$(EXECUTABLE): main.o $(OBJECTS)
	$(CC) $^ -o $@

%.o: %.c
	$(CC) -c $< $(CFLAGS)

clean:
	rm -f *.o $(EXECUTABLE) unify_test search_test core

.PHONY: clean
