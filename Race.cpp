#include "Member.h"
#include "Race.h"
#include "Track.h"
#include "League.h"
#include <string>

Race::Race(string name, Track *where, League *which_League = nullptr): Name(name), Where(where), Which_League(which_League)
{
   Id = Ids;
   Ids++;

   finished = false;

   if (which_League!= nullptr)
   {
      which_League->Add_Race(*this);
   }

   race_participants.Number_of_runners = 0;
}

Race::Race(Race& race): Name(race.Name), Where(race.Where), Which_League(race.Which_League)
{
    Id = race.Id;
    finished = race.finished;
    race_participants = race.race_participants;
}

Race::~Race()
{
    clear();
}

void Race::Print() const
{   
    cout << "Race: " << Name << "Id: " << get_id() << endl;
    cout << "Track: " << Where->Get_Name() << "Id: " << Where->get_id() << endl;
    if(Which_League!= nullptr)
        cout << "League: " << Which_League->Get_Name() << "Id: " << Which_League->get_id() << endl;
    cout << endl;

    cout << "Status of the race: " << (finished? "finished" : "not finished") << endl;

    if(finished)
    {
        cout << "Winner: ";
        cout << Get_winner()->get_name();
        cout << "Id: " << Get_winner()->get_id() << endl;
        cout << "Time: " << Get_Winner_time() << endl;
    }
        

    cout << "Race participants: " << endl;
    if(!finished)
    {
        for(const auto& participant : race_participants.Runners)
        {
            cout << "Name: " << participant.second->get_name();
            cout << "Id: " << participant.second->get_id() << endl;
        }
    }
    else
    {
        vector<double>::const_iterator time = race_participants.Times.begin();
        vector<unsigned int>::const_iterator places = race_participants.Places.begin();
        for(const auto& participant : race_participants.Runners)
        {
            cout << "Name: " << participant.second->get_name();
            cout << "Id: " << participant.second->get_id() << endl;
            cout << "Time: " << *time << endl;
            cout << "Place: " << *places << endl;
            time++;
            places++;
        }
    }
}

void Race::Finish_race()
{
    Assign_places();
    Declare_winner();
    Calculate_average_time();

    Where->Finish_race(Id);
    finished = true;
}
double Race::Get_Average_time() const
{
    if(finished) return race_participants.Average_time;
}
double Race::Get_Winner_time() const
{
    if(finished) return race_participants.Winner_time;
}
double Race::Get_time(unsigned int id) const
{  
    auto const& participant = race_participants.Runners.find(id);
    if(participant->first != id)
    {
        int i=0;
        for(map<unsigned int, Member*>::const_iterator temp = race_participants.Runners.begin(); temp != participant; temp++)
        {
            i++;
        }
        return race_participants.Times[i];
    }
    // there is no participant with such id
    else return -1;
}
const Member* Race::Get_winner() const
{
    if(finished) return race_participants.Winner;
}