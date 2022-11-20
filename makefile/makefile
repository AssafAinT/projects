CC = gcc
ERRFLAG = -ansi -pedantic-errors -Wall -Wextra
OPT = -O3
MODEFLAGS = -DNDEBUG $(OPT) 
CFLAGS = $(ERRFLAG) $(MODEFLAGS) -o

all : fooer.out 

fooer.out : foo.o main.o
	$(CC) -o fooer.out foo.o main.o
	
foo.o : foo.c foo.h 
	$(CC) -c foo.c 

main.o : main.c foo.h
	$(CC) -c main.c


debug : main.o foo.o
	$(CC) $(CFLAGS) fooer.out  main.c foo.c

ar : main.o foo.o 
	ar rsc libfoo.ar $^ 

.PHONY : clean	
clean :
	rm *.out *.o *.ar 
	
