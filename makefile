CC=/usr/bin/g++
CFLAGS= -g -Wall -I. -std=c++14
LINKFLAGS= -g -Wall

experiment: main.o 
	$(CC) $(LINKFLAGS) -o experiment main.o

main.o: main.cpp 
	$(CC) $(CFLAGS) -c main.cpp -o main.o
	
clean:
	rm *.o experiment
	rm *.txt

