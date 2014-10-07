# executable files
all: test_awol
# compiler
CC = g++
# compiler flags
CFLAGS = -Wall -std=c++0x
# object files
OBJECTS = test_awol.o awol.o

test_awol: $(OBJECTS) 
	$(CC) $(OBJECTS) $(CFLAGS) -o test_awol 

test_awol.o: test_awol.c 
	$(CC) -c test_awol.c $(CFLAGS) 

awol.o: awol.c awol.h
	$(CC) -c awol.c $(CFLAGS)

clean:
	rm -f test_awol *.o
