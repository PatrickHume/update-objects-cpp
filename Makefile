all: test

test: test.o byteGetter.o testObject.o
	g++ --std=c++11 test.o byteGetter.o testObject.o -o run

byteGetter.o: byteGetter.cpp
	g++ --std=c++11 -c byteGetter.cpp -o byteGetter.o

testObject.o: testObject.cpp byteGetter.hpp
	g++ --std=c++11 -c testObject.cpp -o testObject.o

# Special rule to remove all build files
clean:
	rm -rf *.o test