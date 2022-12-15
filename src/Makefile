CC = gcc
CFLAGS = -std=c11 -Wall -Wextra -Werror
TST_CFLAGS = -g $(CFLAGS)
CLIBS = -lcheck
LIBNAME = s21_matrix.a
LINUX_FLAGS=-lsubunit -lrt -lpthread -lm
VALGRIND_FLAGS=--trace-children=yes --track-fds=yes --track-origins=yes --leak-check=full --show-leak-kinds=all --verbose --log-file=RESULT_VALGRIND.txt
OS := $(shell uname -s)

all : $(LIBNAME)

$(LIBNAME): *.c *.h
	$(CC) $(CFLAGS) -c *.c
	ar r lib$(LIBNAME) *.o
	rm -f *.o

test:
ifeq ($(OS), Darwin)
	$(CC) $(CFLAGS) *.c ./unit_tests/*.c $(CLIBS) -o tests
else
	$(CC) $(CFLAGS) *.c ./unit_tests/*.c $(CLIBS) -o tests $(LINUX_FLAGS)
endif
	./tests

valgrind:
ifeq ($(OS), Darwin)
	$(CC) $(CFLAGS) *.c ./unit_tests/*.c $(CLIBS) -o tests
else
	$(CC) $(CFLAGS) *.c ./unit_tests/*.c $(CLIBS) -o tests $(LINUX_FLAGS)
endif
	CK_FORK=no valgrind $(VALGRIND_FLAGS) ./tests

clean:
	rm -f *.o
	rm -f *.out
	rm -f *.a
	rm -f tests
	rm -f *.log
	rm -f s21_matrix
	rm -f RESULT_VALGRIND.txt