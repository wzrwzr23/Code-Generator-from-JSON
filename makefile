CXX = g++
FLAGS = -ansi -pedantic -Wall -Werror

assign1: part1 part2 part3

part1: part1.o
	gcc part1.o -o part1

part1.o: pt1Josiah.c
	gcc -c pt1Josiah.c $(FLAGS) -o part1.o

part2: part2.o
	$(CXX) part2.o -o part2

part2.o: asgm2p2.cpp
	$(CXX) -c asgm2p2.cpp -o part2.o

part3: part3.o
	$(CXX) part3.o -o part3

part3.o: pt3.cpp
	$(CXX) -c pt3.cpp -o part3.o

clean:
	rm -rf *.o part1 part2 part3