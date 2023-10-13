
all: clean main

main: main.c
	gcc -o main main.c -lpthread 

clean:
	rm -f main

.PHONY: clean