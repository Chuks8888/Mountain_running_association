# include "Track.h"
# include "Member.h"
# include "Race.h"
unsigned int Track::Ids = 0;

Track::Track(string name, Mountain mountain, int length, unsigned int difficulty)
{
	// Gives the object its id and increases the number of objects i.e. Ids
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
	} else cout << "No races held on this track yet." << endl;

    cout << "Average Time to Finish: " << Average_time << " seconds" << endl;

	Print_Best();
}

void Track::Print_Best()  const
{
	if (Best_time.runner != nullptr)
	{
        cout << "Best Runner: " << Best_time.runner->get_name()<< endl;
        cout << "Best Time: " << Best_time.time << " seconds" << endl;
	} 
	else
		cout << "No best runner recorded yet." << endl;
}

void Track::Print_future_race() const
{
	cout << "Future races: " << endl << endl;
	for(const auto& race : Data)
	{
		if(!race.second->Is_finished())
		{
			cout << "Name: " << race.second->get_name();
			cout << "ID: " << race.second->get_id() << endl;
		}
	}
}

void Track::Add_race(Race& race)
{
	// Inserts the Race* into the Data parameter
	// map<unsigned int (ID of race), Race*> Data;
	Data.insert({race.get_id(), &race});
}

void Track::Finish_race(unsigned int raceId)
{
	const auto& i = Data.find(raceId);
	if(raceId == i->first)
	{
		if(!i->second->Is_finished())
		{
			// Swithces the finished bollean to 1
			i->second->Finish_race();

			// Checks if the winner of the race has the best time
			Compare_best(const_cast<Member*>(i->second->Get_winner()), i->second->Get_Winner_time());

			// Calculates the average time now also 
			// using the new data from the finished race
			Recalculate_average();
		}
	}
	
}

