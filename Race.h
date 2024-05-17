#ifndef RACE
#define RACE

#pragma once
#include "Association.h"

class Race
{
	friend Association;
	friend League;

    public:
		//	Constructors, to construct a Race we need to have 
		//	selected a Track and a league for it, if the Track is nullptr
		//	then the construction will not happen
        Race(string name, Track *where, League *which_League = nullptr);
        Race(Race&);

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

		// Removes all runners from the race and removes other pointers
		// only used during the deconstruction
		void clear();

		//	Methods that are called after the race has finished
        void Calculate_average_time(); 
		void Assign_places(); 
        void Declare_winner();
		
};

#endif
