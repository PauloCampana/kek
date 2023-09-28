SOURCES := $(wildcard src/*.c)
OBJECTS := $(SOURCES:src/%.c=obj/%.o)
COMPILER = clang
FLAGS = -std=c2x -Wall -Wextra -pedantic -O2
LIBS = -lm

run: bin
	@./bin

bin: main.c kek.h $(OBJECTS)
	@$(COMPILER) $(FLAGS) $< -o $@ $(OBJECTS) $(LIBS)

$(OBJECTS): obj/%.o : src/%.c kek.h
	@mkdir -p obj
	@$(COMPILER) $(FLAGS) -c $< -o $@

clean:
	@rm -rf obj
	@rm -f bin
