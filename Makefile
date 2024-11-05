CXXFLAGS= -Wall -Wextra -std=c++17 -O3

all: tests.out tests2.out

tests.out: tests.o Game.o 
	g++ $(CXXFLAGS) -o $@ $^ -lgtest

tests2.out: tests2.o 
	g++ $(CXXFLAGS) -o $@ $^ -lgtest

clean:
	rm -f *.out *.o

