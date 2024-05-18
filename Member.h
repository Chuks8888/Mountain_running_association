#ifndef MEMBER
#define MEMBER

#include "Association.h"

class Member
{
	friend Association;

    public:
		//	For the constructor all one needs are those parameters or
		//	simply use the copy constructor. However I cannot see any
		//	use for the copy construtor
        Member(string name, int age, const char gender = '-', int membership = 1);
        Member(Member&);

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
        void Add_race(const Race&);
        void Remove_race(Race&);
		void Remove_race(const unsigned int);

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

#endif
