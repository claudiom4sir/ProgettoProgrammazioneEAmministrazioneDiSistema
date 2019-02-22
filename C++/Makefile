CCFLAGS = -Wall -pedantic

main.exe: main.o person.o
	g++ main.o person.o -o main.exe
	rm -fr *.o
	
main.o: main.cpp
	g++ $(CCFLAGS) -c main.cpp
	
person.o: person.cpp person.h
	g++ $(CCFLAGS) -c person.cpp