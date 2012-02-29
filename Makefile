SRCDIR = ./src
TESTDIR = ./test
ODIR=./obj
IDIR =./src/include

CC=gcc
CFLAGS=-I$(IDIR) -Wall -Werror -pedantic -std=c99 

_DEPS = PWSData.h PWSLinkedList.h PWSHashFunctions.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ = PWSData.o PWSLinkedList.o PWSHashFunctions.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

_TESTS = PWSDataTest.o PWSLinkedListTest.o CuTest.o AllTests.o
TESTS = $(patsubst %,$(TESTDIR)/%,$(_TESTS))

main: libAlgNData.a

test: buildtests

$(TESTDIR)/%.o: $(TESTDIR)/%.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

buildtests: libAlgNData.a gentests $(TESTS)
	$(CC) $(TESTS) -o run-all-tests -I./test $(CFLAGS) ./libAlgNData.a
	./run-all-tests

gentests:
	$(TESTDIR)/make-tests.sh $(TESTDIR)/*.c > $(TESTDIR)/AllTests.c

$(ODIR)/%.o: $(SRCDIR)/%.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

libAlgNData.a: $(OBJ)
	ar rs $@ $^

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o $(TESTDIR)/*.o run-all-tests libAlgNData.a

