#include "Association.h"
#include <string>
using namespace std;

unsigned int Member::Ids = 0;

Member::Member(string name, int age, const char gender, int membership): Name(name), Age(age), Gender(gender), Membership(membership)
{
	const unsigned int temp = Ids;
	Id = Ids;
	Ids++;

	Performance_index = 0.0;
}

Member::Member(const Member& member)
{
	Id = member.Id;
	if (member.Ids > Ids)
		Ids = member.Ids;

	Name = member.Name;
	Age = member.Age;
	Gender = member.Gender;
	Membership = member.Membership;

	Performance_index = member.Performance_index;
}

Member::~Member()
{
	if(!empty())
	{
		for(auto& race: Participation)
		{
			race.second->Remove_runner(Id);
		}
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

	if(!empty())
	{
		cout << "Participated in race: " << endl;

		for(auto& race: Participation)
		{
			cout << "Race: " << race.second->get_name() << " " << race.second->get_id() << endl;
		}
	}
	else
		cout << "Not participated in any races";
}

long Member::Calculate_performance()
{
	Performance_index = 0;
	if(Membership != 2)
		return 0;

	if(empty())
		return 0;

	map<unsigned int, Race*>::const_iterator i = Participation.begin();
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

void Member::Add_race(const Race &race1)
{
	if(!Find_race(race1.get_id()))
	{
		const Race* race = &race1;
		Participation.insert({const_cast<Race*>(race)->get_id(), const_cast<Race*>(race)});
	}
	else
		cerr << "The member already participates this race";
}

void Member::Remove_race(Race& race)
{
	race.Remove_runner(*this);
	Remove_race(race.get_id());
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
	return Find_race(race.get_id());
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
