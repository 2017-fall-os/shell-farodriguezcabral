all: shell

CFLAGS = -g -O2

shell: shell.o mytoc.o saferFork.o
	cc -o shell shell.o mytoc.o saferFork.o
clean:
	rm -f *.o shell shell.exe
