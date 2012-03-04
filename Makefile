# Directories

SRCDIR = ./src
TESTDIR = ./test
OUTDIR = ./out
ODIR = $(OUTDIR)/obj
TESTODIR = $(OUTDIR)/test-obj
IDIR = ./src/include

# Toolchain

CC = gcc
CFLAGS = -I$(IDIR) -Wall -Werror -pedantic -std=c99
AR = ar

ifdef MACH
	MACH_ARG = -mmcu=$(MACH) 
endif

# Files

LIB = libAlgData.a

_DEPS = PWSData.h PWSLinkedList.h PWSHashFunctions.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ = PWSData.o PWSLinkedList.o PWSHashFunctions.o
ifdef CROSS_COMPILE
	ODIR = $(OUTDIR)/$(CROSS_COMPILE)obj
	OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))
else
	OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))
	TESTOBJ = $(patsubst %,$(TESTODIR)/%,$(_OBJ))
endif

_TESTS = PWSDataTest.o PWSLinkedListTest.o CuTest.o AllTests.o
TESTS = $(patsubst %,$(TESTODIR)/%,$(_TESTS))

# Make stuff

.PHONY: main test gentests profile clean
.PRECIOUS: %/.d

# To handle dependencies to output directories

%/.d:
	mkdir -p $(@D)
	touch $@

# Build
#
# make CROSS_COMPILE=avr- MACH=atmega328 for cross compile to AVR.

main: $(OUTDIR)/$(CROSS_COMPILE)$(LIB)

$(ODIR)/%.o: $(SRCDIR)/%.c $(DEPS) $(ODIR)/.d
	$(CROSS_COMPILE)$(CC) -c -o $@ $< $(CFLAGS) $(MACH_ARG)

$(OUTDIR)/$(CROSS_COMPILE)$(LIB): $(OBJ) $(OUTDIR)/.d
	$(CROSS_COMPILE)$(AR) rs $@ $^

# Test

test: $(OUTDIR)/test-$(LIB) gentests $(TESTS) $(OUTDIR)/gcov/.d
	clang $(TESTS) -o $(OUTDIR)/run-all-tests -I./test $(CFLAGS) $(OUTDIR)/test-$(LIB) -fprofile-arcs -ftest-coverage
	$(OUTDIR)/run-all-tests
	gcov -l -o$(TESTODIR) $(SRCDIR)/*.c 2> /dev/null > $(OUTDIR)/gcov/summary.txt
	mv *.gcov $(OUTDIR)/gcov

gentests:
	$(TESTDIR)/make-tests.sh $(TESTDIR)/*.c > $(TESTDIR)/AllTests.c

$(TESTODIR)/%.o: $(TESTDIR)/%.c $(DEPS) $(TESTODIR)/.d
	clang -c -o $@ $< $(CFLAGS)

$(TESTODIR)/%.o: $(SRCDIR)/%.c $(DEPS) $(TESTODIR)/.d
	clang -c -o $@ $< $(CFLAGS) -fprofile-arcs -ftest-coverage

$(OUTDIR)/test-$(LIB): $(TESTOBJ) $(OUTDIR)/.d
	$(AR) rs $@ $^

# Profile

profile: buildprofilelib

# Clean

clean:
	rm -rf $(OUTDIR)
