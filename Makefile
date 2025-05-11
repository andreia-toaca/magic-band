CFLAGS=-std=c99

build: tema1

tema1: tema1.o
	gcc tema1.o -o tema1 -lm -Wall

tema1.o: tema1.c
	gcc $(CFLAGS) -c tema1.c

run: build
	./tema1

clean:
	rm *.o tema1
