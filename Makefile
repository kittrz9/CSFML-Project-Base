CC = gcc
SHELL = /bin/bash
LIBS = -lcsfml-graphics -lcsfml-window -lcsfml-system -lm
CFLAGS = -Wall -O3
SOURCES = ${wildcard *.c}
NAME = thing

${NAME}: $(SOURCES)
	$(CC) $(CFLAGS) $(SOURCES) $(LDFLAGS) -o $@ $(LIBS)
	
debug: $(SOURCES)
	$(CC) $(CFLAGS) -g $(SOURCES) $(LDFLAGS) -o ${NAME}-debug $(LIBS)

clean:
	rm ./${NAME}
