#ifndef TRACK
#define TRACK

#pragma once
#include "Association.h"

class Track
{
	friend Association;

    public:
		// Constructors
        Track(string name, Mountain mountain, int length, unsigned int difficulty = 5);
        Track(Track&);

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

		// Removes the Race object pointer from Data map
		// removing a race may also remove the best runner
		// When called with the cons reference it deletes the 
		// Race object from existence in the Association
		// If by Id then we simply change its track
		// Both methods can only be called with the 
		// Association object
        void Remove_race(Race&); 
        void Remove_race(const unsigned int);

		// finishes race with give race id
		// which calculates the average time 
		// and looks for best time to compare it to
		// the current one on the track
		void Finish_race(unsigned int);
		
		// Gets name of the track
		string Get_Name() const;

		//	gets id parameter
        const unsigned int get_id() const;
		
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

		//	Checks if a winner of a race has the best time
		void Compare_best(Member*, float time);
	
		//	after a race is finished or destroyed the average time has to change
		double Recalculate_average(); 

		//	gets reference to parameters
        unsigned int& get_difficulty(); double& get_length(); double& get_average();
};

#endif
