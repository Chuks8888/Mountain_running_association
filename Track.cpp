# include "Track.h"
# include "Member.h"
# include "Race.h"

Track::Track(string name, Mountain &mountain, int length, unsigned int difficulty)
{
	// Gives the object its id and increases the number of objects i.e. Ids
	Id = Ids;
	Ids ++;

	Name = name;
	Where = &mountain;
	mountain.mountains_tracks.insert({Id, this});
	Difficulty = (difficulty < 1) ? 1 : (difficulty > 10 ? 10 : difficulty);
	Length = length;

	Average_time = 0.0;
	Best_time.runner = nullptr;

	// Fix this issue, because when best time is 0 then we cannot
	// assign any members to the Best_time.runner
	Best_time.time = 0.0;
}

Track::~Track()
{
	while(!Data.empty())
	{
		Race *temp = Data.begin()->second;
		delete temp;
	}

	Best_time.runner = nullptr;

	if(Where)
		Where->mountains_tracks.erase(Id);
	Where = nullptr;

	cerr << "Track " << Name << " deleted" << endl;
}

 void Track::Print() const 
{
    cout << "\nTrack Name: " << Name << endl;
    cerr << "Location: " << Where->Name << endl;
    cout << "Difficulty: " << Difficulty << "/10" << endl;
    cout << "Length: " << Length << " kilometers" << endl;
    if (!Data.empty()) 
	{
        cout << "Number of Races: " << Data.size() << endl;
        cout << "Races:\n";

        for (const auto& pair : Data) 
		{
            cout << "Race ID: " << pair.first;
            cout << " Name: " << pair.second->get_name() << endl; 
        }
    	cout << "Average Time to Finish: " << Average_time << " minutes" << endl;
		Print_Best();

	} else cout << "No races held on this track yet." << endl;
	cerr << endl;
}

void Track::Print_Best()  const
{
	if (Best_time.runner != nullptr)
	{
        cout << "Best Runner: " << Best_time.runner->get_name()<< endl;
        cout << "Best Time: " << Best_time.time << " minutes" << endl;
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
	if(race.get_id() != Data.find(race.get_id())->first)
	{
		Data.insert({race.get_id(), &race});
	}
	else
	    cout << "Race with ID " << race.get_id() << " already exists." << endl;

}

void Track::Finish_race(unsigned int raceId)
{
	map<unsigned int, Race*>::const_iterator i = Data.find(raceId);
	if(raceId == i->first)
	{
		if((i->second->Is_finished()) && (i->second->Get_winner() != nullptr))
		{
			// Checks if the winner of the race has the best time
			search_for_best();

			// Calculates the average time now also 
			// using the new data from the finished race
			Recalculate_average();
		}
	}
}

string Track::Get_Name() const
{
	return Name;
}

const map<unsigned int, Race*> Track::Get_Data() const
{
	return Data;
}

const pair<float, Member*> Track::Get_Best_time() const
{
	if(Best_time.runner!= nullptr)
	{
		pair<float, Member*> temp = {Best_time.time, Best_time.runner};
		return temp;	
	} 
	return make_pair(0.0, nullptr);
}
double Track::get_average_time() const
{
	return Average_time;
}

double Track::operator-=(double decrease)
{
	if(Length > decrease && Length > 0)
		Length -= decrease;
	return Length;
}

double Track::operator+=(double increase)
{
	Length += increase;
	return Length;
}

unsigned int Track::operator++()
{
	if(Difficulty <= 10)
		Difficulty++;
	return Difficulty;
}

unsigned int Track::operator--()
{
	if(Difficulty > 1)
		Difficulty--;
	return Difficulty;
}

Member* Track::search_for_best()
{
	if(Data.empty())
	{
		Best_time.runner = nullptr;
		return nullptr;
	}

	Best_time.time = 0.0;
	for(const auto& race : Data)
	{
		if(race.second->Is_finished())
			Compare_best(const_cast<Member*>(race.second->Get_winner()), race.second->Get_Winner_time());
	}
	return Best_time.runner;
}

void Track::Compare_best(Member* winner, float time)
{
	if((Best_time.time > time) || (Best_time.time == 0.0))
	{
		Best_time.runner = winner;
		Best_time.time = time;
	}
}

void Track::Remove_race(Race& race)
{
	Race* temp = Data.find(race.get_id())->second;

	//Removing the race from Data parameter
	Remove_race(temp->get_id());

	// Deleting the Race object
	if(temp == &race)
		delete temp;
} 

void Track::Remove_race(const unsigned int id)
{
	Race* temp = Data.find(id)->second;
	if(temp && temp->get_id() == id)
	{
		// Erasing the race object form the Data of the track
		Data.find(id)->second = nullptr;
		Data.erase(id);

		// After removing the race we need to recalculate the
		// the average time to finish the track
		Recalculate_average();

		// After removing the Race object from the Track object
		// We check if the best time holder gained that status due
		// to the now deleted race
		if(temp->Get_winner() && (temp->Get_winner() == Best_time.runner && temp->Get_Winner_time() == Best_time.time))
			search_for_best();
	}
}

double Track::Recalculate_average()
{
	int denominator = 0;
	double time = 0.0;
	for(const auto& race : Data)
	{
		if(race.second->Is_finished())
		{
			denominator++;
			time += race.second->Get_Average_time();
		}
	}

	// Check if we would divide by 0
	if(denominator == 0)
		return 0.0;

	Average_time = (time/denominator);
	return Average_time;
}

unsigned int& Track::get_difficulty()
{
	return Difficulty;
} 

double& Track::get_length()
{
	return Length;
} 

double& Track::get_average()
{
	return Average_time;
}

const unsigned int Track::get_id() const
{
	return Id;
}
