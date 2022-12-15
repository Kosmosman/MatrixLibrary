CC = gcc
CFLAGS = -std=c11 -Wall -Wextra -Werror
CLIBS = -lcheck
LIBNAME = s21_matrix.a

all : $(LIBNAME)

$(LIBNAME): *.c *.h
	$(CC) $(CFLAGS) -c *.c
	ar r lib$(LIBNAME) *.o
	rm -f *.o

test: $(LIBNAME)
	$(CC) $(CFLAGS) *.c ./unit_tests/*.c $(CLIBS) -o tests
	./tests

clean:
	rm -f *.o
	rm -f *.out
	rm -f *.a
	rm -f tests
	rm -f *.log