SRCDIR = ./src
TESTDIR = ./test
IDIR =./src/include
CC=gcc
CFLAGS=-I$(IDIR) -std=c99 -pedantic

ODIR=obj

_DEPS = PWSLinkedList.h PWSHashFunctions.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ = PWSLinkedList.o PWSHashFunctions.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

_TESTS = PWSLinkedListTest.o CuTest.o AllTests.o
TESTS = $(patsubst %,$(TESTDIR)/%,$(_TESTS))

main: libAlgNData

test: buildtests

$(ODIR)/%.o: $(TESTDIR)/%.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

buildtests: libAlgNData gentests $(TESTS)
	$(CC) $(TESTS) -o run-all-tests -I./test $(CFLAGS)
	./run-all-tests

gentests:
	$(TESTDIR)/make-tests.sh $(TESTDIR)/*.c > $(TESTDIR)/AllTests.c

$(ODIR)/%.o: $(SRCDIR)/%.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

libAlgNData: $(OBJ)
	$(CC) -shared -o $@ $^ $(CFLAGS)

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o $(TESTDIR)/*.o run-all-tests libAlgNData

