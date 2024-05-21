all: compile clean

compile:
	g++ -g -c Member.cpp -c Race.cpp -c Track.cpp -c Main.cpp -c League.cpp
	g++ Member.o Race.o Track.o Main.o League.o -o Test

clean:
	rm *.o
