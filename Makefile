CXX_FLAG = --std=c++11 -g

all: test

test: testbst.o intbst.o
	g++ $(CXX_FLAG) -o testbst testbst.o intbst.o

intbst.o: intbst.cpp
	g++ -c $(CXX_FLAG) intbst.cpp

testbst.o: testbst.cpp
	g++ -c $(CXX_FLAG) testbst.cpp

clean:
	rm -f test *.o
