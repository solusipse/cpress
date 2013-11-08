CC=gcc
LFLAGS=-fPIC -c
CFLAGS=-O2 -Wall
BUILDDIR=build
EXAMPLESDIR=src/examples
prefix=/usr/local

all:
	mkdir $(BUILDDIR)
	$(CC) -o $(BUILDDIR)/cpress.o $(LFLAGS) $(CFLAGS) src/cpress.c
	$(CC) -o $(BUILDDIR)/cpress.so -shared $(BUILDDIR)/cpress.o

example:
	$(CC) -o example $(CFLAGS) $(EXAMPLESDIR)/example.c

clean:
	rm -rf *o main example