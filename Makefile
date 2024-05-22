all: compile clean

compile:
	g++ -g -c Member.cpp -c Race.cpp -c Track.cpp -c Main.cpp -c League.cpp -c Association.cpp
	g++ Member.o Race.o Track.o Main.o League.o Association.o -o Test

clean:
	del *.o
