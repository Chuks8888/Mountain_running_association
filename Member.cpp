#include "Member.h"
#include "Race.h"
#include <string>
using namespace std;

Member::Member(string name, int age, const char gender, int membership): Name(name), Age(age), Gender(gender), Membership(membership)
{
	const unsigned int temp = Ids;
	Id = Ids;
	Ids++;

	Performance_index = 0.0;
}

Member::Member(Member& member)
{
	Id = member.Id;	
	Name = member.Name;
	Age = member.Age;
	Gender = member.Gender;
	Membership = member.Membership;

	Performance_index = member.Performance_index;
}

Member::~Member()
{
	clear();
}

void Member::clear()
{
	while(!Participation.empty())
	{
		for(auto& race : Participation)
		{
			race.second->Remove_runner(*this);
			break;
		}
	}
	cerr << "Member " << Name << " deleted" << endl;
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
		cout << "Not participated in any races" << endl;
	cout << endl;
}

long Member::Calculate_performance()
{
	Performance_index = 0;
	if(Membership != 2)
		return 0;

	if(empty())
		return 0;

	double weight = 1.0;
	double total_weight = 0.0;

	for (auto& race : Participation)
	{
		double time = race.second->Get_time(Id);
		double avg_time = race.second->Get_Average_time();
		double difference = avg_time - time;

		if(difference <= -7.0) 
			Performance_index += 1000 * weight;

		else if(difference <= -5.0)
			Performance_index += 500 * weight;

		else if(difference <= 0)
			Performance_index += 100 * weight;

		if(difference >= 7.0)
			Performance_index -=1000 * weight;

		else if(difference >=5.0)
			Performance_index -=500 * weight;

		else if(difference >0)
			Performance_index -=100 * weight;

		total_weight += weight;
        weight *= 0.9;
	}
	return (this->Performance_index / total_weight);
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

void Member::Add_race(Race &race1)
{
	if(!race1.Find_runner(Id))
	{
		return;
	}

	if(!Find_race(race1.get_id()))
	{
		Participation.insert({race1.get_id(), &race1});
	}
	else
		cerr << "The member already participates this race";
}

void Member::Remove_race(Race& race)
{
	race.Remove_runner(this->Id);
	Remove_race(race.get_id());
} 

void Member::Remove_race(const unsigned int id)
{
	if(!empty())
	{
		const auto& i = Participation.find(id);
		if(i->first == id)
			Participation.erase(id);
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

const unsigned int Member::get_id() const
{
	return Id;
}

const string Member::get_name() const
{
	return Name;
}

unsigned int Member::get_membership() const
{
	return Membership;
}

bool Member::empty() const
{
	return Participation.empty();
}
