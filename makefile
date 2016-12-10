main: test.o vector.o
	g++ -o main test.o vector.o

test.o: test.cpp 
	g++ -c test.cpp

vector.o: vector.h vector.cpp
	g++ -c vector.cpp
clean:
	rm *.o
	

