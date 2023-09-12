OBJECTS = obj/random.o obj/basicstat.o obj/print.o obj/read.o obj/write.o
FLAGS = -O3 -Wall -Wextra -pedantic -std=c2x
LIBS = -lm -lpthread

run: bin
	mkdir -p obj
	./bin

bin: main.c kek.h $(OBJECTS)
	clang $(FLAGS) main.c -o bin $(OBJECTS) $(LIBS)

obj/random.o: src/random.c kek.h
	mkdir -p obj
	clang $(FLAGS) -c src/random.c -o obj/random.o

obj/basicstat.o: src/basicstat.c kek.h
	clang $(FLAGS) -c src/basicstat.c -o obj/basicstat.o

obj/print.o: src/print.c kek.h
	clang $(FLAGS) -c src/print.c -o obj/print.o

obj/read.o: src/read.c kek.h
	clang $(FLAGS) -c src/read.c -o obj/read.o

obj/write.o: src/write.c kek.h
	clang $(FLAGS) -c src/write.c -o obj/write.o

clean:
	rm -rf obj
	rm bin
