#pragma once
#include <iostream>
#include <string.h>
#include <vector>
#include <map>
using namespace std;

struct Mountain;
class Member;
class Track;
class Race;
class League;

class Association
{
    private:
		string Name;
        vector<Member> members; // list of runners
        vector<Track> tracks; // list of running tracks
        vector<Race> races; // list of races (finished, in progress, future)
		vector<League> leagues; // league is just a bigger event than a signle race that consists of races
		vector<Mountain> mountains; // list of mountaints
    public:
        Association(string Name);
        ~Association();
        void Add_Member(Member&); 
        void Add_Track(Track&);
        void Add_Race(Race&);
        void Add_League(League&);
        void Add_Mountain(Mountain&);
};

struct Mountain
{
	string Name;
	string Country;
    map<unsigned int, Track*> mountains_tracks; // Tracks that are on this mountain
	int elevation[2]; // 0 - lowest point ; 1 - highest point
};

class Member
{
	friend Association;
    private:
        static unsigned int Ids;
		const unsigned int Id;
        const string Name;
        int Age;
        const char Gender;
        unsigned int Membership; // 0 - no membership; 1 - standard; 2 - gold
        long Performance_index; // only for gold membership
        map<unsigned int, Race*> Participation;
    public:
        Member(string name, int age, char gender = '-', int membership = 1); // normal constructor
        Member(const Member&); // copy constructor 
        ~Member();
    
        void Print() const;
        long Calculate_performance(); // only for gold memembership
        void Cancel_membership();
        void Gold_membership();
        void Standard_membership();
        void Add_race(const Race&); // uses operator
        void Remove_race(const Race&); void Remove_race(const unsigned int); // uses operator
        bool Find_race(const Race&) const; bool Find_race(const unsigned int) const;
    private:
        unsigned int& get_membership(); // gets reference to the Membership parameter
        unsigned int get_id() const; // gets id of member
        bool empty() const; // checks for any participation

        void operator+(const Race&); // adds a race to the map
        void operator-(const Race&); // removes race from runners map
        void operator-(const unsigned int); // removes race from runners map
        unsigned int operator++(); // increases age by one
        
};

class Track
{
	friend Association;
    friend Race;
    struct Best
    {
        float time;
        Member* runner; 
    };
    private:
        static unsigned int Ids;
		const unsigned int Id;
        const string Name;
		const Mountain *Where; // On what mountain is the track
        int Difficulty; // ranges from 1 - 10
        int Length; // in kilometers
		map<unsigned int, Race*> Schedule; // Schdule of past, present and future races
        double Average_time;
        Best Best_time; // Structure of the track's record time 
    public:
        Track(string name, Mountain mountain, int length, int difficulty = 5); // normal constructor
        Track(const Track&); // copy constructor
        ~Track();

        void Print() const; // Display information about the track
        void Print_Best() const; // Displays more information on best runner
        void Add_race(const Race&); // adds race to the map
        void Remove_race(const Race&); // removing a race may also remove the best runner
        void Remove_race(const unsigned int); // the add and remove method use operators 

        void operator-=(unsigned int); // decreases the length
        void operator+=(unsigned int); // increases the length
        void operator++(); // increase the difficulty
        void operator--(); // decrease the difficulty
    private:
        void operator+(const Race&); // adds a race
        void operator-(const Race&); // removes a race
        void operator-(const unsigned int); // -||-

        void Finish_race(unsigned int); // Used only from object class Race
        Member* search_for_best(); // If the best runner or the race he was in was removed
        double Recalculate_average(); // after a race is finished or destroyed the average time has to change
        int& get_diff(); int& get_length(); int& get_average(); // gets reference to parameters
        const unsigned int get_id();
};

class Race
{
	friend Association;
    struct Participants
    {
        map<unsigned int, Member*> Runners;
        vector<unsigned int> Places;
        vector<double> Times;
        int Number_of_runners;
        double Average_time;
        double winner_time;
    };
    private:
        static unsigned int Ids;
		const unsigned int Id;
        const string Name;
        Track *Where;
        Participants race_participants;
        Member *Winner;
        bool finished;
    public:
        Race(string Name, Track where);
        Race(const Race&);
        ~Race();
        
        void Print() const; // Displays info
        void Finish_race(); // finishes race and calculates places, winner, avg_time etc.
        void Add_runner(const Member&);
        void Remove_runner(const Member&);
        void Remove_runner(const unsigned int);

        void operator=(const Track&); // reaassigns the track
    private:
        void operator+(const Member&); // Add runner
        void operator-(const Member&); // remove runner
        void operator-(const unsigned int); // only if finished = 0

        const unsigned int get_id();
        bool Is_finished() const; // checks if the race is finished
        void Calculate_average(); // calculates average time
        void Assign_places(); // assigns places based on runners's times
        void Declare_winner(); // when race is finished
};

class League
{
	friend Association;
    private:
        static unsigned int Ids;
		const unsigned int Id;
        const string Name;
        const string Reward;
        map<unsigned int, Member*> League_Runners;
        map<unsigned int, Race*> League_Races;
        unsigned int number_of_races; // max 5 races a league
        Member *Winner;
        bool In_progress; // when its 1 no more runners or races can be adeed
        bool finished; // when its 1 the league is over
    public:
        League(string name, string Reward);
        League(const League&);
        ~League();

        void Add_Race(const Race&);
        void Remove_Race(const Race&); void Remove_Race(const unsigned int);
        void Add_runner(const Member&);
        void Remove_runner(const Member&); void Remove_runner(const unsigned int);
        void Start_League(); // stops from adding runners and races
        void Next_stage(); // finishes next race, or finishes league
    private:
        void operator+(const Race&); // adds a race
        void operator-(const Race&);  // removes a race
        void operator+(const Member&); // Add runner
        void operator-(const Member&); // remove runner 
        void Declare_winner(); // declares winner based on average time in all races
        const unsigned int get_id();

};

// Initializing of static parameters
unsigned int Member::Ids = 0;
unsigned int Track::Ids = 0;
unsigned int Race::Ids = 0;
unsigned int League::Ids = 0;