#include "Association.h"

unsigned int Track::Ids = 0;

Track::Track(string name, Mountain mountain, int length, unsigned int difficulty)
{
	Id = Ids;
	Ids ++;

	Name = name;
	Where = &mountain;
	Difficulty = difficulty;
	Length = length;

	Average_time = 0.0;
	Best_time.runner = nullptr;
	Best_time.time = 0.0;
}

 void Track::Print() const 
{
    cout << "Track Name: " << Name << endl;
    cout << "Location: " << Where->Name << endl;
    cout << "Difficulty: " << Difficulty << "/10" << endl;
    cout << "Length: " << Length << " kilometers" << endl;
    
    if (!Data.empty()) 
	{
        cout << "Number of Races: " << Data.size() << endl;
        cout << "Races:\n";

        for (const auto& pair : Data) 
		{
            cout << "Race ID: " << pair.first << endl;
            cout << "Name: " << pair.second->get_name() << endl << endl; 
        }
	} 
	else 
        cout << "No races held on this track yet." << endl;

    cout << "Average Time to Finish: " << Average_time << " seconds" << endl;

    if (Best_time.runner != nullptr)
	{
        cout << "Best Runner: " << Best_time.runner->get_name()<< endl;
        cout << "Best Time: " << Best_time.time << " seconds" << endl;
	} 
	else
		cout << "No best runner recorded yet." << endl;
}

void Track::Print_Best()  const
{
	if (Best_time.runner != nullptr)
	{
        cout << "Best Time: " << Best_time.time << " seconds" << endl;
		Best_time.runner->Print();
	} 
	else
		cout << "No best runner recorded yet." << endl;
}

void Track::Add_race(Race& race)
{
	Data.insert({race.get_id(), &race});
}

void Track::Finish_race(unsigned int raceId)
{
	const auto& i = Data.find(raceId);
	if(raceId == i->first)
	{
		
	}
}


