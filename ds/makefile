FILE = $(run)

# flags
CC = gcc
OBJFLAG = -c
DEPFLAG = -MD
SHARED = -shared
LIBNAME = lib$(FILE)
INCLUDE = include/

MAKEDIR = make_dir/$(FILE)/
OBJDIR := $(MAKEDIR)obj/
LIBDIR := $(MAKEDIR)libraries/
OUTDIR := $(MAKEDIR)out_file/

ifeq ($(G),c)
MODEFLAGS= -DNDEBUG -O3
else
MODEFLAGS= -g
endif

ifeq ($(lib),d)
CFLAGS = -fPIC -ansi -pedantic-errors -Wall -Wextra
DYNFLAG = -L.-Wl,-rpath=$(MAKEDIR)libraries/
else
CFLAGS = -ansi -pedantic-errors -Wall -Wextra
DYNFLAG = 
endif

ifeq ($(FILE), scheduler)
SRCFILES_O=$(OBJDIR)$(FILE).o $(OBJDIR)utils.o $(OBJDIR)uid.o $(OBJDIR)dlist.o $(OBJDIR)task.o\
			$(OBJDIR)pqueue.o $(OBJDIR)srtlist.o
else ifeq ($(FILE), hash)
SRCFILES_O=$(OBJDIR)$(FILE).o $(OBJDIR)utils.o $(OBJDIR)dlist.o
else ifeq ($(FILE), pqueue_heap)
SRCFILES_O=$(OBJDIR)$(FILE).o $(OBJDIR)utils.o $(OBJDIR)heap.o $(OBJDIR)dynamic_vector.o
else ifeq ($(FILE), scheduler_heap)
SRCFILES_O=$(OBJDIR)$(FILE).o $(OBJDIR)utils.o $(OBJDIR)uid.o $(OBJDIR)heap.o $(OBJDIR)task.o\
			$(OBJDIR)pqueue_heap.o $(OBJDIR)dynamic_vector.o
else ifeq ($(FILE), heap)
SRCFILES_O=$(OBJDIR)$(FILE).o $(OBJDIR)utils.o $(OBJDIR)dynamic_vector.o
else ifeq ($(FILE), trie)
SRCFILES_O=$(OBJDIR)$(FILE).o $(OBJDIR)utils.o 
else ifeq ($(FILE), dhcp)
SRCFILES_O=$(OBJDIR)$(FILE).o $(OBJDIR)trie.o 
else ifeq ($(FILE), knight_tour)
SRCFILES_O=$(OBJDIR)$(FILE).o $(OBJDIR)bit_array.o $(OBJDIR)utils.o 
else
SRCFILES_O=$(OBJDIR)$(FILE).o $(OBJDIR)utils.o
endif


runfile : $(OUTDIR)$(FILE).out | $(OUTDIR)
	./$(OUTDIR)$(FILE).out
	
gdb: $(OUTDIR)$(FILE).out | $(OUTDIR)
	gdb $(OUTDIR)$(FILE).out
cgdb: $(OUTDIR)$(FILE).out | $(OUTDIR)
	cgdb $(OUTDIR)$(FILE).out

vlg: $(OUTDIR)$(FILE).out | $(OUTDIR)
	valgrind --leak-check=yes --track-origins=yes $(OUTDIR)$(FILE).out

$(OUTDIR)$(FILE).out : $(LIBDIR)$(LIBNAME).so $(OBJDIR)$(FILE)_test.o| $(OUTDIR)
	$(CC) $(DYNFLAG) $(OBJDIR)$(FILE)_test.o $(TESTFILES) -I $(INCLUDE) -o $@ $<

$(LIBDIR)$(LIBNAME).so : $(SRCFILES_O) | $(LIBDIR)
	$(CC) $(DEPFLAG) $(SHARED) -o $@ $^

$(OBJDIR)$(FILE)_test.o : test/$(FILE)_test.c | $(OBJDIR)
	$(CC) $(DEPFLAG) $(MODEFLAGS) $(CFLAGS) -I $(INCLUDE) $(OBJFLAG) -o $@ $<

$(OBJDIR)%.o : src/%.c| $(OBJDIR)
	$(CC) $(DEPFLAG) $(MODEFLAGS) $(CFLAGS) -I $(INCLUDE) $(OBJFLAG) -o $@ $<

	
$(OUTDIR): ; @mkdir -p $@
$(LIBDIR): ; @mkdir -p $@
$(OBJDIR): ; @mkdir -p $@

# delete .d files, compiled .o files
clean: $(MAKEDIR)
	rm -r $(MAKEDIR)


