MotokoLib
=========

A library of algorithms and data structures implemented in C.

To build:

    make

To cross-compile for e.g. AVR:

    make CROSS_COMPILE=avr- MACH=atmega328

To test:

    make test

Coverage output is saved in $(OUTDIR)/gcov.

To profile:

    make profile

Profiling output is saved in $(OUTDIR)/profile.log.

To clean:

    make clean

Content
-------

MotokoHeap - A small memory handling utility with reference counting, autorelease and buffer overrun checks.
MotokoLinkedList - A linked list implementation.
MotokoBuffer - A circular buffer.
