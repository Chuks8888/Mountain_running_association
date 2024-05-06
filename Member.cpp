#include "Association.h"
#include <string>
using namespace std;

unsigned int Member::Ids = 0;

Member::Member(string name, int age, const char gender, int membership)
{
	const unsigned int temp = Ids;
	Id = Ids;
	Ids++;

	Name = name;
	Age = age;
	Gender = gender;
	Membership = membership;

	Performance_index = 0.0;
}

Member::~Member()
{
	if(!empty())
	{
		map<unsigned int, Race*>::const_iterator i = Participation.begin();
		do
		{
			i->second->Remove_runner(Id);
			++i;
		} while (i != Participation.end());
		Participation.clear();
	}
}

void Member::Print() const
{
	cout << "Runner: " << Name << endl;
	cout << "ID: " << Id << endl;
	cout << "Membership: " << Membership << endl;
	if(Membership == 2)
		cout << "Performance index: " << Performance_index << endl;
	cout << "Gender: " << Gender << endl;
	cout << "Age: " << Age << endl;
	cout << "Participated in race: " << endl;

	if(!Participation.empty())
	{
		map<unsigned int, Race*>::const_iterator i = Participation.begin();
		do
		{
			cout << i->first << " " << i->second << endl;
			++i;
		} while (i != Participation.end());
	}
}

long Member::Calculate_performance()
{
	Performance_index = 0;
	if(Membership != 2)
		return 0;

	if(empty())
		return 0;

	map<unsigned int, Race*>::const_iterator i;

	i = Participation.begin();
	if(Participation.size() > 5)
		for(int j = 0; j <Participation.size()-5; j++)
			i++;

	for(i; i != Participation.end(); ++i)
	{
		double time = i->second->Get_time(Id);
		double avg_time = i->second->Get_Average_time();
		double difference = avg_time - time;

		if(difference <= -7.0) 
			Performance_index += 1000;

		else if(difference <= -5.0)
			Performance_index += 500;

		else if(difference <= 0)
			Performance_index += 100;

		if(difference >= 7.0)
			Performance_index -=1000;

		else if(difference >=5.0)
			Performance_index -=500;

		else if(difference >0)
			Performance_index -=100;
	}
	return this->Performance_index;
}

void Member::Cancel_membership()
{
	Membership = 0;
}

void Member::Gold_membership()
{
	Membership = 2;
}

void Member::Standard_membership()
{
	Membership = 1;
}

unsigned int Member::operator++()
{
	Age++;
	return Age;
}

void Member::Add_race(Race &race)
{
	Participation.insert({race.get_id(), &race});
}

void Member::Remove_race(Race& race)
{
	race.Remove_runner(*this);
} 

void Member::Remove_race(const unsigned int id)
{
	if(!empty())
	{
		map<unsigned int, Race*>::const_iterator i = Participation.find(id);
		if(i->first == id)
			i->second->Remove_runner(*this);
		else
			cerr<<"race not found";
	}
}

bool Member::Find_race(const Race& race) const
{
	if(empty())
		return 0;
	map<unsigned int, Race*>::const_iterator i = Participation.find(race.get_id());
	if(i->second == &race)
		return 1;
	return 0;
} 
bool Member::Find_race(const unsigned int id) const
{
	if(empty())
		return 0;
	map<unsigned int, Race*>::const_iterator i = Participation.find(id);
	if(i->first == id)
		return 1;
	return 0;
}

const map<unsigned int, Race*> Member::Get_Participation() const
{
	return Participation;
}

unsigned int Member::get_membership() const
{
	return Membership;
}

const unsigned int Member::get_id() const
{
	return Id;
}

bool Member::empty() const
{
	return Participation.empty();
}