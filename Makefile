all: compile clean

compile:
	g++ -g -c Member.cpp -c Race.cpp -c Track.cpp -c Main.cpp -c League.cpp -c Association.cpp -c Tests.cpp
	g++ Member.o Race.o Track.o Main.o League.o Association.o Tests.o -o Mountaint_Association

clean:
	rm *.o
