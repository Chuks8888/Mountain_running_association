#pragma once
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
        Association(string Name);

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
        void Edit_Race(unsigned int id);
        void Edit_League(unsigned int id);
		void Edit_Member(unsigned int id);
		void Edit_Track(unsigned int id);

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

class Member
{
	friend Association;

    public:
		//	For the constructor all one needs are those parameters or
		//	simply use the copy constructor. However I cannot see any
		//	use for the copy construtor
        Member(string name, int age, const char gender = '-', int membership = 1);
        Member(const Member&);

		//	The deconstructor of Member object, removes the pointers pointing
		//	to it the object from other classes like League, Race, Track
        ~Member();
    
		//	Prints the information about the member and
		//	the names and ids of the races he/she has taken part in
        void Print() const;

		//	This method calculates the performance of the runner
		//	Based on the time he/she gets on different races
        long Calculate_performance();

		//	Methods that change the membership of the runner
        void Cancel_membership();
        void Gold_membership();
        void Standard_membership();

		//	increases age by one
        unsigned int operator++();

		//	Adds/Removes a Race object pointer to/from the 
		//	Participation parameter, which is a map of Race 
		//	object pointers where the key is the id of the race
        void Add_race(Race&);
        void Remove_race(Race&); void Remove_race(const unsigned int);

		//	Find the race if the Member took part in it
		//	either do it by id of race or its object
        bool Find_race(const Race&) const; bool Find_race(const unsigned int) const;

		// Get method used for testing
		const map<unsigned int, Race*> Get_Participation() const;

		//	gets id of member
        const unsigned int get_id() const;

		//	Gets name of the runner
		const string get_name() const;

	private:
		//	the static parameter Ids keeps track of how
		//	many objects of class Member were created,
		//	and it is used to assign the Id parameter.
		//	This is done so that there arent people with 
		//	the same id, if the class is loaded from txt file
		//	the parameter Ids will take the highest value there is
        static unsigned int Ids;
		unsigned int Id;

        string Name;
        int Age;
        char Gender;

		//	0 - no membership; 1 - standard; 2 - gold
        unsigned int Membership; 
		//	only for gold membership
        long Performance_index; 

		//	This is a map of pointers of races in which
		//	the Member took part int, with
		//	key being the id of the race.
        map<unsigned int, Race*> Participation;

		//	gets Membership parameter
        unsigned int get_membership() const;

		// checks for any participation
        bool empty() const; 

};

class Track
{
	friend Association;

    public:
		// Constructors
        Track(string name, Mountain mountain, int length, unsigned int difficulty = 5);
        Track(const Track&);

		//	If the Track is being deconstructed we need to remove
		//	all of the things that point to it. For example
		//	If we were to remove a Track
		//	that had like 10 Races on it already,
		//	We would then need to remove those 10 races too

		// Display information about the track
        void Print() const; 

		// Displays more information on best runner
        void Print_Best() const; 

		// prints unfinished races
		void Print_future_race() const; 

        // adds race to the map in the Data parameter
		void Add_race(Race&);

		// finishes race with give race id
		// which calculates the average time 
		// and looks for best time to compare it to
		// the current one on the track
		void Finish_race(unsigned int);

		// Removes the Race object pointer from Data map
		// removing a race may also remove the best runner
        void Remove_race(const Race&); 
        void Remove_race(const unsigned int);
		
		// Get method used for testing
		const map<unsigned int, Race*> Get_Data() const;

    private:
		//	Best structure holds a pointer to the
		//	Member class object that achieved the 
		//	Best tme of all on this race track
		struct Best
		{
			float time;
			Member* runner; 
		};

		//	Structure of the track's record time
        Best Best_time;

		//	The static paramater Ids work pretty much
		//	the same as in class Member
        static unsigned int Ids;
		unsigned int Id;
        string Name;

		//	Pointer to the mountain where the track
		//	is located
		Mountain *Where; 
		
		//	ranges from 1 - 10
        unsigned int Difficulty;

		//	In kilometers
        double Length; 

		//	Pointers of past, present and future races
		//	The key to the map is Race's Id
		map<unsigned int, Race*> Data; 

		//	Average time it takes to finish the track
		//	its is calculated from Data collected form
		//	Races held on this track
        double Average_time;

        double operator-=(double); // decreases the length
        double operator+=(double); // increases the length
        unsigned int operator++(); // increase the difficulty
        unsigned int operator--(); // decrease the difficulty
        
		//	If the best runner or the race he was in was removed
        Member* search_for_best();        
	
		//	after a race is finished or destroyed the average time has to change
		double Recalculate_average(); 

		//	gets reference to parameters
        int& get_difficulty(); int& get_length(); int& get_average();

		//	gets id parameter
        const unsigned int get_id() const;
};

class Race
{
	friend Association;
	friend League;

    public:
		//	Constructors, to construct a Race we need to have 
		//	selected a Track and a league for it, if the Track is nullptr
		//	then the construction will not happen
        Race(string Name, Track *where, League *Which_League = nullptr);
        Race(const Race&);

		//	The deconstruction of the Race, means that we need
		//	to remove all the object pointing to it, i.e.
		//	class Member, class Track, class League
        ~Race();

        // Displays info on race
        void Print() const;         
		
		//	finishes race and uses the public method Finish_race
		//	from object Track *Where parameter	
		void Finish_race(); 

		// Parameter getting methods
		// Most likely will be used by class Track object
		// when its calcualting its parameters
		double Get_Average_time() const;
		double Get_Winner_time() const;
		double Get_time(unsigned int id) const;
		const Member *Get_winner() const;

		// Adds/Removes a runner to the Race, and ads/removes Race pointer
		// to The Member's Participation map
        void Add_runner(const Member&);
        void Remove_runner(const Member&);
        void Remove_runner(const unsigned int);

		// Used to get the pointer to the Track object
		const Track* Get_Where() const;

		// Get method used for testing
		const map<unsigned int, Member*> Get_Participants() const;

		//	Gets id of the race
        const unsigned int get_id() const;

		//	Gets the name of the race
		const string get_name() const;

		//	checks if the race is finished
        bool Is_finished() const; 
	
	//	The structure Participants, holds information of
	//	who is taking part in the race, how many people.
	//	Also after the race is finished it holds a pointer
	//	to the winner and other parameters like Average time
    struct Participants
    {
		//	Map of runners, key is their id
        map<unsigned int, Member*> Runners;
		
		//	These vectors follow the same indexing
		//	as the map, so if someone is [0] in the 
		//	Runners map, then their index is also going 
		//	to be [0] in the Places vector and Times vector 
        vector<unsigned int> Places;
        vector<double> Times;

        int Number_of_runners;

		//	Parameters after the race is finished
        double Average_time;
		Member *Winner;
        double Winner_time;
    };

    private:
		//	The Ids parameter works the same as in
		//	Track or Member class
        static unsigned int Ids;
		unsigned int Id;
        string Name;

		//	Pointer to the Track where the 
		//	Race takes place
        Track *Where;

		//	Pointer to the League it is a part of
		//	If it is not a part of any, it's just nullptr
		League *Which_League;

		//	Structure parameter that was explained above
        Participants race_participants;

		//	Bolean for when the race is finished
        bool finished;

		// reaassigns the track
		// Therefore removing the Race pointer from
		// the Track "Data" map
        void operator=(const Track&);

		//	Methods that are called after the race has finished
        void Calculate_average_time(); 
		void Assign_places(); 
        void Declare_winner();
};

class League
{
	friend Association;
    public:
		// Constructors
        League(string name, string Reward);
        League(const League&);

		// Removing a League from existance requires
		// removing Race pointers from other classes
		// i.e. Member, Track
        ~League();

		// Ads a Race to the League, and assigns runners to the 
		// race that are already in the League_runners map
        void Add_Race(const Race&);

		// Removing a Race is the same as just using the Race
		// deconstructor
        void Remove_Race(const Race&); void Remove_Race(const unsigned int);

		// Ads a runner to the League, and assigns him/her 
		// to all the races that are defined in the League class
        void Add_runner(const Member&);

		// Removing a runner acts as removing him from
		// All the races belonging to the league
        void Remove_runner(const Member&); void Remove_runner(const unsigned int);

		// stops from edditing the league
        void Start_League();

		// finishes next race, or finishes league
        void Next_stage(); 

		// get method for the winner member
		const Member *Get_winner() const;

		// temporary get method used for testing
		const map<unsigned int, Member*> Get_Runners() const;
		const map<unsigned int, Race*> Get_Races() const;

    private:

		//	Works the same as in the previous classes
        static unsigned int Ids;
		unsigned int Id;
        string Name;
	
		//	This time there is a reward, since its a league
		//	But the reward is a string so it can be either
		//	the sum of money in words, or a trophy, it all
		//	depedns on the users choice
        string Reward;
		
		//	Like the Race, a League has its map of runners
		//	All of the runners are automatically assigend to all 
		//	the races in the League
        map<unsigned int, Member*> League_Runners;

		//	The league has its own map of Race pointers
		//	the key is Race object's id
		//	max 5 races a league
        map<unsigned int, Race*> League_Races;
        unsigned int number_of_races; 

		//	The winner of the league
        Member *Winner;

		//	when its 1 no more runners or races can be adeed
        bool In_progress; 
		//	when its 1 the league is over
        bool finished;

		// 0 - still under construction, 1 - in progress, 2 - finished
		int Get_status();
	
		// declares winner based on average time in all races
        void Declare_winner(); 

		// gets if of the League
        const unsigned int get_id() const;

};
