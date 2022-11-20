
BINARY=$(EX).out
SRCDIRS=src
TESTDIRS=test
INCDIRS=include

DEPFLAGS=-MP -MMD

CC=gcc
OPT=-O3
ERRFLAGS=-ansi -pedantic-errors -Wall -Wextra

ifeq ($(G),c)
MODEFLAGS=-DNDEBUG $(OPT)
else
MODEFLAGS=-g
endif

CFLAGS=$(ERRFLAGS) $(MODEFLAGS) $(foreach D,$(INCDIRS),-I$(D)) $(DEPFLAGS)


ifeq ($(EX), schedular)
SRCFILES=$(foreach D,$(SRCDIRS),$(wildcard $(D)/$(EX).c)) src/uid.c src/pqueue.c src/srtlist.c src/dlist.c src/scheduler.c src/task.c
TESTFILES=$(foreach D,$(TESTDIRS),$(wildcard $(D)/$(EX)_test.c))
else
SRCFILES=$(foreach D,$(SRCDIRS),$(wildcard $(D)/$(EX).c)) 
TESTFILES=$(foreach D,$(TESTDIRS),$(wildcard $(D)/$(EX)_test.c))
endif

OBJECTS=$(patsubst %.c,%.o,$(SRCFILES) $(TESTFILES))
DEPFILES=$(patsubst %.c,%.d,$(SRCFILES) $(TESTFILES))

.PHONY: all
all: vlg

vlg: $(BINARY)
	valgrind --leak-check=yes --track-origins=yes ./$(BINARY)
	make clean EX=$(EX)

run: $(BINARY)
	./$(BINARY)

a.out: $(BINARY)

$(BINARY): $(OBJECTS)
	$(CC) -o $@ $^

arch: $(OBJECTS)
	ar rcs $(EX).ar $^

symb:$(OBJECTS)
	nm $(OBJECTS)

%.o:%.c
	$(CC) $(CFLAGS) -c -o $@ $<

.PHONY: clean
clean:
	rm -rf $(BINARY) $(OBJECTS) $(DEPFILES)

