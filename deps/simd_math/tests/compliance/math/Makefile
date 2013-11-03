all: math_compliance

clean:
	rm *.o math_compliance -f

math_compliance: math_compliance.o
	gcc -o math_compliance math_compliance.o -L../../../src/ -lSIMDx86 -lm
math_compliance.o: math_compliance.c
	gcc -c -O3 -fomit-frame-pointer -I../../../include math_compliance.c
