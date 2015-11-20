all: sim
sim: main.o structs_define.h structs_initialize.h
	gcc -o sim main.c -lm -g
clean:
	rm -rf sim main.o
