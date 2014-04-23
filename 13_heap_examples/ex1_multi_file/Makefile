###### format for makefile: ######

#target: dependencies
# 	how to create target

all: test_complex

complex.o : complex.c complex.h
	clang -c complex.c

test_complex : test_complex.c complex.o
	clang -o test_complex test_complex.c complex.o

clean:
	rm -rf *.o

clobber: clean
	rm -rf test_complex
