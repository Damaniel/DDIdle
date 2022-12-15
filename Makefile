CC=gcc
CFLAGS=-O2 -Wall
DEPS=include/ddunidle.h include/structs.h include/inventry.h include/skills.h
LIBS=-lalleg

all: ddunidle

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

ddunidle: src/main.o src/exptable.o src/skills.o
	$(CC) -o ddunidle.exe src/main.o src/exptable.o src/skills.o $(LIBS)

prod: ddunidle
	strip ddunidle.exe


clean: 
	rm -f *.exe src/*.o
