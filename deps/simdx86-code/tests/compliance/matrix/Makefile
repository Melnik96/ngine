all: matrix_compliance

clean:
	rm *.o  matrix_compliance -f

matrix_compliance: matrix_compliance.o
	gcc -o matrix_compliance matrix_compliance.o -L../../../bin -lSIMDx86
matrix_compliance.o: matrix_compliance.c
	gcc -c -O3 -fomit-frame-pointer -I../../../include matrix_compliance.c
