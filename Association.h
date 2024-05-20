#ifndef ASSOCIATION
#define ASSOCIATION

#include <iostream>
#include <string.h>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

class Association;
class Member;
class Race;
class Track;
class League;
struct Mountain;

class Association
{

    public:
		//	Constructor of mountain running associaition all we need is a name.
        Association(string name);

		//	When the deconstructor is invoked all the information
		//	of the class is going to be stored to a txt file
        ~Association();

		//	There are two methods to add one of the below, 
		//	one can either do all of it manually, or when the data
		//	is being read from txt files, the methods return the id
		//	of the thing being added
        unsigned int Add_Member(Member&);    unsigned int Add_Member();
        unsigned int Add_Track(Track&);     unsigned int Add_Track();
        unsigned int Add_Race(Race&);       unsigned int Add_Race();
        unsigned int Add_League(League&);   unsigned int Add_League();

		//	The same goes for the mountain structure, there are two
		//	ways of adding one
        void Add_Mountain(Mountain&);
		void Add_Mountain();

		//	Those methods are a way to interactively change the
		//	parameters within the stored classes
		//	For example change participants of the race, change
		//	someones membership, or progress a league or finish a race
		//	Those however have limitations, example: if a race has 
		//	finished we cannot change who participated in the race, 
		//	unless we want to remove that person from the system as a whole
        int Edit_Race(unsigned int id); // 1
        int Edit_League(unsigned int id); // 2
		int Edit_Member(unsigned int id); // 3
		int Edit_Track(unsigned int id); // 4

		//	Prints the information on the classes the associaition has
        int Print_Unfinished_Races() const; // the int is for number of races 
		int Print_Finished_Races() const; 
		int Print_All_Races() const;
        void Print_Members() const;
        void Print_Tracks() const;
		void Print_Leagues() const;
		void Print_Mountains() const;

		// Getting the objects to check their content
		// ONLY USED FOR TESTING
		map<unsigned int, Member*> Get_member_map() const;
        map<unsigned int, Track*> Get_tracks_map() const;
        map<unsigned int, Race*> Get_races_map() const;
		map<unsigned int, League*> Get_leagues_map() const;
		vector<Mountain*> Get_mountaints_vector() const; 

    private:
		//	Name of the associaition
		string Name;

		//	The main class has a map of all the objects added to it
		//	all elements of the map are pointers with keys being the ids
		//	of the objects, so when adding objects manually we
		//	need to dynamically alocate them using new
        map<unsigned int, Member*> members;
        map<unsigned int, Track*> tracks;
        map<unsigned int, Race*> races;
		map<unsigned int, League*> leagues;

		//	Since Mountain is a struct we do not need to use 
		//	ids or a map for it
		vector<Mountain*> mountains; 

};

struct Mountain
{
	string Name;
	string Country;

	//highest point in meters
	int Height;
	
	//	Map of Track object pointers, that are assigned
	//	when constructing a Track object, the key is the 
	//	Track id
    map<unsigned int, Track*> mountains_tracks;
 
};

#endif
