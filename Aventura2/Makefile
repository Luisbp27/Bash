# Makefile del proyecto Aventura 2

CC=gcc # compilador
CFLAGS=-c -g -Wall -std=c99 #flags para el compilador
LDFLAGS= #flags para enlazador

SOURCES=my_shell.c
PROGRAMS=my_shell

OBJS=$(SOURCES:.c)

all: $(OBJS) $(PROGRAMS)

my_shell: my_shell.c $(LIBRARIES) $(INCLUDES)
	$(CC) $(LDFLAGS) $(LIBRARIES) $< -o $@

%.o: %.c $(INCLUDES) 
	$(CC) $(CFLAGS) -o $@

.PHONY: clean
clean:
	rm -rf *.o $(PROGRAMS)