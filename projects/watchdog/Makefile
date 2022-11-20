#EX=program name without .c
#To run with VLG: VLG=vlg
#To see reachable blocks with VLG: VLG=vlgs 
#For DNDEBUG add MOD=D

USRPROCESS=$(EX).out

MODFLAGS=-DNDEBUG
VLGFLAGS=
CC=gcc
OPT=-O3
ERRFLAGS=-ansi -pedantic-errors -Wall -Wextra
CFLAGS=$(OPT) $(ERRFLAGS)

LIBWD_SRCS=src/watchdog.c src/uid.c src/pqueue_heap.c src/scheduler_heap.c src/heap.c src/dynamic_vector.c src/task.c src/utils.c
WDPROCESS_SRCS=src/uid.c src/pqueue_heap.c src/scheduler_heap.c src/heap.c src/dynamic_vector.c src/task.c src/utils.c
WDPROCESS_FLAGS=-lpthread
OBJECT_FILES=heap.o libwatchdog.so pqueue_heap.o scheduler_heap.o dynamic_vector.o task.o uid.o utils.o watchdog_process.out watchdog.o
EXECUTABLE_FLAGS=-lwatchdog -pthread

ifeq ($(VLG), vlg)
VLGFLAGS=valgrind --leak-check=yes --track-origins=yes
else ifeq ($(VLG), vlgs)
VLGFLAGS=valgrind --leak-check=yes --track-origins=yes --leak-check=full --show-leak-kinds=all
endif

ifeq ($(MOD), D)
MODFLAGS=
endif

all: 
	$(CC) -c -fpic $(MODFLAGS) -iquote include $(LIBWD_SRCS)
	$(CC) -shared -o libwatchdog.so *.o
	$(CC) -L. $(MODFLAGS) -o watchdog_process process/watchdog_process.c -iquote include/ $(WDPROCESS_SRCS) -lwatchdog $(WDPROCESS_FLAGS)
	$(CC) -L. $(MODFLAGS) -I include -o $(USRPROCESS) client/$(EX).c $(EXECUTABLE_FLAGS)
	LD_LIBRARY_PATH=. $(VLGFLAGS) ./$(USRPROCESS)

.PHONY: clean
clean:
	rm $(USRPROCESS) $(OBJECT_FILES)

