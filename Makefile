run:
COMPILER = clang
FLAGS = -std=c2x -Wall -Wextra -pedantic -O2
LIBS = -lm

SOURCES := $(shell find src -type f -name '*.c')
OBJECTS := $(addsuffix .o, $(basename $(patsubst src%, build%, $(SOURCES))))

$(foreach s, 								\
	$(SOURCES), 							\
	$(foreach o, 							\
		$(filter %$(basename $(notdir $s)).o, $(OBJECTS)),	\
		$(eval $o: $s) 						\
	) 								\
)

run: build/bin
	@./build/bin

build/bin: main.c kek.h $(OBJECTS)
	@$(COMPILER) $(FLAGS) $< -o $@ $(OBJECTS) $(LIBS)

$(OBJECTS):
	@$(if $(wildcard $(@D)),,mkdir -p $(@D))
	@$(COMPILER) $(FLAGS) -c $< -o $@

clean:
	@rm -rf build
	@rm -f bin
