#include "League.h"
#include "Race.h"
#include "Member.h"

const unsigned int League::get_id() const
{
    return Id;
}

void League::Add_Race(Race& race)
{
    // TODO: Add runners to the race list
    League_Races.insert({race.get_id(), &race});

}

void League::Remove_race(const unsigned int id)
{
    const auto& race = League_Races.find(id);
    if(race->first == id)
    {
        Race* temp = race->second;
        League_Races.erase(id);
        delete temp;
    }
    else cout << "Race not found" << endl;
}

string League::Get_Name() const
{
    return Name;
}