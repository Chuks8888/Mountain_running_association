#include "League.h"
#include "Race.h"
#include "Member.h"

League::League(string name, string Reward) : Name(name), Reward(Reward)
{
    Id = Ids;
    Ids++;

    Winner = nullptr;

    number_of_races = 0;
    In_progress = 0;
    finished = false;
}

League::~League()
{
	for(auto& race : League_Races)
	{
		Race* temp = race.second;
		race.second =  nullptr;
		temp->Which_League =  nullptr;
		delete temp;
	}
	League_Races.clear();
    League_Runners.clear();
	cerr << "League " << Name << " deleted" << endl;
}

void League::Add_Race(Race& race)
{
    if(In_progress)
    {
        cout << "League is in progress" << endl;
        return;
    }

    if(number_of_races == 5)
    {
        cout << "Maximum number of races reached" << endl;
        return;
    }

    if(race.race_participants.Number_of_runners == 0)
    {
        League_Races.insert({race.get_id(), &race});
        for(auto& participant : League_Runners)
            race.Add_runner(*participant.second);
        
        race.Which_League = this;
        number_of_races++;
    }
    else
        cout << "Race already has runners" << endl;
}

void League::Remove_race(Race& race)
{
    if(&race == League_Races.find(race.get_id())->second)
    {
        delete &race;
    }
}

void League::Remove_race(const unsigned int id)
{
    const auto& race = League_Races.find(id);
    if(race->first == id)
    {
        race->second->Which_League = nullptr;
        race->second->clear();
        League_Races.erase(id);

        number_of_races--;

        if(finished)
            Declare_winner();
    }
    else cout << "Race not found" << endl;
}

void League::Add_runner(Member& runner)
{
    if(In_progress == 0)
    {
        League_Runners.insert({runner.get_id(), &runner});
        for(auto& race : League_Races)
        {
            race.second->Add_runner(runner);
        }
    }
    else cout << "League is in progress" << endl;
}

void League::Remove_runner(Member& runner)
{
	int i = League_Runners.find(runner.get_id())->first;
	int j = runner.get_id();
    if(i == j)
    {
        League_Runners.erase(runner.get_id());
        for(auto& race : League_Races)
        {
			race.second->Which_League = nullptr;
            race.second->Remove_runner(runner);
			race.second->Which_League = this;
        }

        if(finished)
            Declare_winner();
    }
}

void League::Remove_runner(const unsigned int id)
{
    if(id == League_Runners.find(id)->second->get_id())
    {
        League_Runners.erase(id);
        for(auto& race : League_Races)
        {
			race.second->Which_League = nullptr;
            race.second->Remove_runner(id);
			race.second->Which_League = this;
        }

        if(finished)
            Declare_winner();
    }
}

bool League::find_runner(const unsigned int id) const
{
    if(League_Runners.find(id)->first == id)
	{
		return true;
	}
    
    return false;
}

void League::Start_League()
{
    In_progress = 1;
}

void League::Next_stage()
{
    if(!In_progress)
    {
        cout << "League has not started" << endl;
        return;
    }

    if(finished)
    {
        cout << "League already finished" << endl;
        return;
    }

    for(auto& race : League_Races)
    {
        if(!race.second->Is_finished())
        {
            race.second->Finish_race();
            if(race.first == League_Races.end()->first)
                break;
            return;
        }
    }
    finished = true;
    Declare_winner();
}

const Member* League::Get_winner() const
{
    return Winner;
}

string League::Get_Name() const
{
    return Name;
}

const unsigned int League::get_id() const
{
    return Id;
}

int League::Get_status() const
{
    if(finished)
        return 2;
    else 
	{
        if(In_progress)
            return 1;
		else
			return 0;
	}
}

const map<unsigned int, Member*> League::Get_Runners() const
{
    return League_Runners;
}

const map<unsigned int, Race*> League::Get_Races() const
{
    return League_Races;
}

void League::Declare_winner()
{
    if(number_of_races == 0)
    {
        Winner = nullptr;
        return;
    }

    vector<pair<double, unsigned int>> Times;

    for(const auto& runner : League_Runners)
        Times.push_back({0.0, runner.first});

    for(const auto& race : League_Races)
    {
        for(int i = 0; i < League_Runners.size(); i++)
        {
            Times[i].first += race.second->race_participants.Times[i];
        }
    }

    sort(Times.begin(), Times.end());

    Winner = League_Runners.find(Times[0].second)->second;
    cout << "Winner of the league " << Name << "is " << Winner->get_name() << " with average time " << Times[0].first << endl;
}
