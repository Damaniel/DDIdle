CC=gcc
CFLAGS=-O2 -Wall
DEPS=include/ddunidle.h include/structs.h include/inventry.h include/skills.h include/fileutil.h
LIBS=-lalleg

all: ddunidle

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

ddunidle: src/main.o src/exptable.o src/skills.o src/fileutil.o
	$(CC) -o ddunidle.exe src/main.o src/exptable.o src/skills.o src/fileutil.o $(LIBS)

prod: ddunidle
	strip ddunidle.exe


clean: 
	rm -f *.exe src/*.o
