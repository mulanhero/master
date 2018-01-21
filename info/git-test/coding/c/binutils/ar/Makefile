CC = gcc
CFLAGS = -g -Wall -I./
LDFLAGS = -L./ -lfoobar

BIN = test

test: libfoobar.a

libfoobar.a: foo.o bar.o
	ar -q  $@ $^

all: $(BIN)

clean:
	rm -rf $(BIN) *.o *.dSYM *.a
