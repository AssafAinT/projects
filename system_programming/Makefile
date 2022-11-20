FILE=$(EX).out
SRCDIRS=src
TESTDIRS=test
INCDIRS=include
CC = gcc
ERRFLAG = -ansi -pedantic-errors -Wall -Wextra
OPT = -O3
MODEFLAGS = -DNDEBUG $(OPT) 
CFLAGS=$(ERRFLAGS) $(MODEFLAGS) $(foreach D,$(INCDIRS),-I$(D)) $(DEPFLAGS)

ifeq ($(EX), scheduler)
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

vlg: $(FILE)
	valgrind --leak-check=yes --track-origins=yes ./$(FILE)
	make clean EX=$(EX)

run: $(FILE)
	./$(FILE)

a.out: $(FILE)


$(FILE): $(OBJECTS)
	$(CC) -o $@ $^

arch: $(OBJECTS)
	ar rcs $(EX).ar $^

symb:$(OBJECTS)
	nm $(OBJECTS)

%.o:%.c
	$(CC) $(CFLAGS) -c -o $@ $<

.PHONY: clean
clean:
	rm -rf $(FILE) $(OBJECTS) $(DEPFILES)

