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
    if (Which_League!= nullptr)
    {
        Which_League->Remove_Race(*this);
    }

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
    if(finished)
    {
        
    }
    else
    {

    }
}