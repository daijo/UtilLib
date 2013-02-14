UtilLib
=======

A library containing useful tools and utilities.

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

Features
--------

* Heap - A small memory handling utility with reference counting, autorelease and buffer overrun checks.
* LinkedList - A linked list implementation.
* MsgQueue - A message queue using Unix domain sockets.

Backlog
-------

* Log
* MergeSort
* Dictionary
* Tree
