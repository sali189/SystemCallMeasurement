output: main.o
	g++ main.o -o experiment

main.o: main.cpp
	g++ -c main.cpp
	
clean:
	rm *.o experiment
	rm *.txt file
