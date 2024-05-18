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
        delete race.second;
    }
    League_Races.clear();
    League_Runners.clear();
}

void League::Add_Race(Race& race)
{
    if(In_progress)
    {
        cout << "League is in progress" << endl;
        return;
    }

    if(race.race_participants.Number_of_runners == 0)
    {
        League_Races.insert({race.get_id(), &race});
        for(auto& participant : League_Runners)
            race.Add_runner(*participant.second);
    }
    else
        cout << "Race already has runners" << endl;
}

void League::Remove_race(Race& race)
{
    if(&race == League_Races.find(race.get_id())->second)
    {
        Remove_race(race.get_id());
        race.~Race();
    }
}

void League::Remove_race(const unsigned int id)
{
    // Calling with id means we dont want to remove
    // the whole race object, but just the runners
    // and the league
    const auto& race = League_Races.find(id);
    if(race->first == id)
    {
        Track *temp = race->second->Where;
        race->second->clear();
        race->second->Where = temp;
        League_Races.erase(id);
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

string League::Get_Name() const
{
    return Name;
}

const unsigned int League::get_id() const
{
    return Id;
}