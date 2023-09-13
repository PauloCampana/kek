OBJECTS =                                    \
	obj/vec.o obj/basic.o obj/random.o       \
	obj/basicstat.o obj/print.o obj/read.o   \
	obj/write.o
COMPILER = gcc
FLAGS = -O3 -Wall -Wextra -pedantic -std=c2x
LIBS = -lm -lpthread

run: bin
	mkdir -p obj
	./bin

bin: main.c kek.h $(OBJECTS)
	$(COMPILER) $(FLAGS) main.c -o bin $(OBJECTS) $(LIBS)

obj/vec.o: src/vec.c kek.h
	mkdir -p obj
	$(COMPILER) $(FLAGS) -c src/vec.c -o obj/vec.o

obj/basic.o: src/basic.c kek.h
	$(COMPILER) $(FLAGS) -c src/basic.c -o obj/basic.o

obj/random.o: src/random.c kek.h
	$(COMPILER) $(FLAGS) -c src/random.c -o obj/random.o

obj/basicstat.o: src/basicstat.c kek.h
	$(COMPILER) $(FLAGS) -c src/basicstat.c -o obj/basicstat.o

obj/print.o: src/print.c kek.h
	$(COMPILER) $(FLAGS) -c src/print.c -o obj/print.o

obj/read.o: src/read.c kek.h
	$(COMPILER) $(FLAGS) -c src/read.c -o obj/read.o

obj/write.o: src/write.c kek.h
	$(COMPILER) $(FLAGS) -c src/write.c -o obj/write.o

clean:
	rm -rf obj
	rm bin
