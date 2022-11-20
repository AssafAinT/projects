FILE = $(run)

# flags
PP = g++
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
CFLAGS = -fPIC std=c++98 -ansi -pedantic-errors -Wall -Wextra 
DYNFLAG = -L.-Wl,-rpath=$(MAKEDIR)libraries/
else
CFLAGS = std=c++98-ansi -pedantic-errors -Wall -Wextra
DYNFLAG = 
endif

SRCFILES_O=$(OBJDIR)$(FILE).o 


runfile : $(OUTDIR)$(FILE).out | $(OUTDIR)
	./$(OUTDIR)$(FILE).out
	
gdb: $(OUTDIR)$(FILE).out | $(OUTDIR)
	gdb $(OUTDIR)$(FILE).out
cgdb: $(OUTDIR)$(FILE).out | $(OUTDIR)
	cgdb $(OUTDIR)$(FILE).out

vlg: $(OUTDIR)$(FILE).out | $(OUTDIR)
	valgrind --leak-check=yes --track-origins=yes $(OUTDIR)$(FILE).out

$(OUTDIR)$(FILE).out : $(LIBDIR)$(LIBNAME).so $(OBJDIR)$(FILE)_test.o| $(OUTDIR)
	$(PP) $(DYNFLAG) $(OBJDIR)$(FILE)_test.o $(TESTFILES) -I $(INCLUDE) -o $@ $<

$(LIBDIR)$(LIBNAME).so : $(SRCFILES_O) | $(LIBDIR)
	$(PP) $(DEPFLAG) $(SHARED) -o $@ $^

$(OBJDIR)$(FILE)_test.o : test/$(FILE)_test.c | $(OBJDIR)
	$(PP) $(DEPFLAG) $(MODEFLAGS) $(CFLAGS) -I $(INCLUDE) $(OBJFLAG) -o $@ $<

$(OBJDIR)%.o : src/%.c| $(OBJDIR)
	$(PP) $(DEPFLAG) $(MODEFLAGS) $(CFLAGS) -I $(INCLUDE) $(OBJFLAG) -o $@ $<

	
$(OUTDIR): ; @mkdir -p $@
$(LIBDIR): ; @mkdir -p $@
$(OBJDIR): ; @mkdir -p $@

# delete .d files, compiled .o files
clean: $(MAKEDIR)
	rm -r $(MAKEDIR)


