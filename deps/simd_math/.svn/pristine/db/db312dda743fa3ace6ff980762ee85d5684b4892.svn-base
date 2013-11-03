all: quaternion_compliance

clean:
	rm *.o quaternion_compliance

quaternion_compliance: quaternion_compliance.o
	gcc -o quaternion_compliance quaternion_compliance.o -L../../../bin -lSIMDx86 -lm
quaternion_compliance.o : quaternion_compliance.c
	gcc -c -O3 -fomit-frame-pointer -I../../../include quaternion_compliance.c
