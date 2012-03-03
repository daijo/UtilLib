# Directories

SRCDIR = ./src
TESTDIR = ./test
ODIR = ./obj
IDIR = ./src/include
OUTDIR = 

# Toolchain

CC = gcc
CFLAGS = -I$(IDIR) -Wall -Werror -pedantic -std=c99 $(MACH_ARG)
AR = ar

ifdef MACH
	MACH_ARG = -mmcu=$(MACH) 
endif

# Files

_DEPS = PWSData.h PWSLinkedList.h PWSHashFunctions.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ = PWSData.o PWSLinkedList.o PWSHashFunctions.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

_TESTS = PWSDataTest.o PWSLinkedListTest.o CuTest.o AllTests.o
TESTS = $(patsubst %,$(TESTDIR)/%,$(_TESTS))

# Build
#
# make CROSS_COMPILE=avr- MACH=atmega328 for cross compile to AVR.

main: libAlgNData.a

$(ODIR)/%.o: $(SRCDIR)/%.c $(DEPS)
	$(CROSS_COMPILE)$(CC) -c -o $@ $< $(CFLAGS)

libAlgNData.a: $(OBJ)
	$(CROSS_COMPILE)$(AR) rs $@ $^

# Test

test: libAlgNData.a gentests $(TESTS)
	$(CC) $(TESTS) -o run-all-tests -I./test $(CFLAGS) ./libAlgNData.a
	./run-all-tests

$(TESTDIR)/%.o: $(TESTDIR)/%.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

gentests:
	$(TESTDIR)/make-tests.sh $(TESTDIR)/*.c > $(TESTDIR)/AllTests.c

# Profile

profile: buildprofilelib

# Clean

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o $(TESTDIR)/*.o run-all-tests libAlgNData.a callgrind.out.*

