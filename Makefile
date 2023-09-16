SOURCES := $(wildcard src/*.c)
OBJECTS := $(SOURCES:src/%.c=obj/%.o)
COMPILER = gcc
FLAGS = -std=c2x -Wall -Wextra -pedantic -O3
LIBS = -lm -lpthread

run: obj/_main
	@./obj/_main

obj/_main: main.c kek.h $(OBJECTS)
	@$(COMPILER) $(FLAGS) $< -o $@ $(OBJECTS) $(LIBS)

$(OBJECTS): obj/%.o : src/%.c kek.h
	@$(COMPILER) $(FLAGS) -c $< -o $@

clean:
	@rm obj/*.o
	@rm obj/_main
