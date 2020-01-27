CC=clang
CFLAGS=-Wall

all: seqprinter

seqprinter: main.o sequence.o
	$(CC) $(CFLAGS) -o $@ $^

test: seqprinter
	./seqprinter

# these rules say to rebuild main.o and sequence.o if sequence.h changes
main.o: main.c sequence.h
sequence.o: sequence.c sequence.h

clean:
	$(RM) -f seqprinter *.o
