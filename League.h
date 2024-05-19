#ifndef LEAGUE
#define LEAGUE

#pragma once
#include "Association.h"

class League
{
	friend Association;
    public:
		// Constructors
        League(string name, string Reward);
        League(League&);

		// Removing a League from existance requires
		// removing Race pointers from other classes
		// i.e. Member, Track
        ~League();

		// Ads a Race to the League, and assigns runners to the 
		// race that are already in the League_runners map
        void Add_Race(Race&);

		// Removing a Race is the same as just using the Race
		// deconstructor
        void Remove_race(Race&); void Remove_race(const unsigned int);

		// Ads a runner to the League, and assigns him/her 
		// to all the races that are defined in the League class
        void Add_runner(Member&);

		// Removing a runner acts as removing him from
		// All the races belonging to the league
        void Remove_runner(Member&); void Remove_runner(const unsigned int);

		// Finds if a runner is in the League
		bool find_runner(const unsigned int) const;

		// stops from edditing the league
        void Start_League();

		// finishes next race, or finishes league
        void Next_stage(); 

		// get method for the winner member
		const Member *Get_winner() const;

		// Gets the name of the league
		string Get_Name() const;

		// gets id of the League
        const unsigned int get_id() const;

		// 0 - still under construction, 1 - in progress, 2 - finished
		int Get_status() const;

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
	
		// declares winner based on average time in all races
        void Declare_winner(); 

};

#endif
