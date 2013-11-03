all: vector_compliance

clean:
	rm -f *.o vector_compliance

vector_compliance.o: vector_compliance.c
	gcc -c vector_compliance.c -I../../../include -Os -fomit-frame-pointer

vector_compliance: vector_compliance.o
	gcc -o vector_compliance vector_compliance.o -L../../../bin -lSIMDx86
