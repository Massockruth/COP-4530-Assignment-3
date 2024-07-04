#Ruth Massock
#06/28/2024
#Assignment 4
all: 
	g++ -std=c++11 -c  in2post.cpp
	g++ -std=c++11 -c  stack.h
	g++ -std=c++11 in2post.o -o in2post.x 


clean:
	rm -f *.o *.x
