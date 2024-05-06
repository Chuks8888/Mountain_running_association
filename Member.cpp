#include "Association.h"
#include <string>
using namespace std;

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


	for(map<unsigned int, Race*>::const_iterator i = Participation.begin(); i != Participation.end(); ++i)
	{
		cout << i->first << " " << i->second << endl;
	}
}

long Member::Calculate_performance()
{
	Performance_index = 0.0;
	if(Membership != 2)
		return Membership;

	map<unsigned int, Race*>::const_iterator i;

	if(Participation.size() > 5)


	for(i = Participation.begin(); i != Participation.end(); ++i)
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
