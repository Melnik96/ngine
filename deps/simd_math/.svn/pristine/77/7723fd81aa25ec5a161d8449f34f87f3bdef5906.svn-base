all: polygon_compliance

clean:
	rm -f *.o polygon_compliance

polygon_compliance.o: polygon_compliance.c
	gcc -c polygon_compliance.c -I../../../include -Os -fomit-frame-pointer

polygon_compliance: polygon_compliance.o
	gcc -o polygon_compliance polygon_compliance.o -L../../../bin -lSIMDx86
