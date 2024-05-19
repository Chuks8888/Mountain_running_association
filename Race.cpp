#include "Member.h"
#include "Race.h"
#include "Track.h"
#include "League.h"
#include <string>

Race::Race(string name, Track *where, League *which_League): Name(name), Where(where), Which_League(which_League)
{
   Id = Ids;
   Ids++;

   finished = false;

   if (which_League!= nullptr)
   {
      which_League->Add_Race(*this);
   }

   race_participants.Number_of_runners = 0;

   where->Add_race(*this);
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
    cerr << "Race " << Name << " deleted" << endl;
}

void Race::Print() const
{   
    cout << "Race name: " << Name << endl << "Race Id: " << get_id() << endl;
    cout << "Track name: " << Where->Get_Name() << endl << "Track Id: " << Where->get_id() << endl;
    if(Which_League!= nullptr)
        cout << "League: " << Which_League->Get_Name() << " Id: " << Which_League->get_id() << endl;
    cout << endl;

    cout << "Status of the race: " << (finished? "finished" : "not finished") << endl;

    if(finished)
    {
        cout << "Winner: ";
        cout << Get_winner()->get_name();
        cout << " Id: " << Get_winner()->get_id() << endl;
        cout << "Winner time: " << Get_Winner_time() << endl << endl;
    }
        

    cout << "Race participants: " << endl;
    if(!finished)
    {
        for(const auto& participant : race_participants.Runners)
        {
            cout << "Name: " << participant.second->get_name();
            cout << " Id: " << participant.second->get_id() << endl;
        }
    }
    else
    {
        vector<double>::const_iterator time = race_participants.Times.begin();
        vector<unsigned int>::const_iterator places = race_participants.Places.begin();
        for(const auto& participant : race_participants.Runners)
        {
            cout << "Name: " << participant.second->get_name();
            cout << " Id: " << participant.second->get_id() << endl;
            cout << "Time: " << *time << endl;
            cout << "Place: " << *places << endl << endl;
            time++;
            places++;
        }
    }
}

void Race::Finish_race()
{
    if(Which_League->Get_status() == 0)
    {
        cout << "The league is not started" << endl;
        return;
    }

    if(!race_participants.Number_of_runners == 0)
    {
        Assign_places();
        Declare_winner();
        Calculate_average_time();

        finished = true;
        Where->Finish_race(Id);

        for(const auto& participant : race_participants.Runners)
            participant.second->Calculate_performance();

        cerr << "Race finished" << endl << endl;
    }
    else
        cout << "There are no participants in the race" << endl;
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
    // check if the race is finished
    if(!finished) return -1;

    auto const& participant = race_participants.Runners.find(id);
    if(participant->first == id)
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

void Race::Add_runner(Member& participant)
{
    // check if the participant is in the league
    if(Which_League != nullptr)
    {
        if(!Which_League->find_runner(participant.get_id()))
        {
            cout << "The member is not a part of this league";
            return;
        }
    }
    // check if the race is finished
    if(!finished)
    {
        if(race_participants.Runners.find(participant.get_id())->second != &participant)
        {
            race_participants.Runners.insert({participant.get_id(), &participant});
            participant.Add_race(*this);
            race_participants.Number_of_runners++;
        }
        else cout << "This participant is already in the race" << endl;
    }
    else
        cout << "The race is finished and new runners cannot be added" << endl;
}

void Race::Remove_runner(Member& participant)
{
    if(Which_League != nullptr)
    {
        if(Which_League->find_runner(participant.get_id()))
        {
            Which_League->Remove_runner(participant);
            return;
        }
    }
    participant.Remove_race(this->Id);
    Remove_runner(participant.get_id());
}

void Race::Remove_runner(const unsigned int id)
{
    const auto& participant = race_participants.Runners.find(id);

    // remove the participant from all league races
    if(Which_League != nullptr)
    {
        if(Which_League->find_runner(id))
        {
            Which_League->Remove_runner(id);
            return;
        }
        if(participant->first != id)
            return;
    }  

    if(participant->first == id)
    {
        if(finished)
        {
            vector<double>::const_iterator time = race_participants.Times.begin();
            vector<unsigned int>::const_iterator place = race_participants.Places.begin();

            for(map<unsigned int, Member*>::const_iterator temp = race_participants.Runners.begin(); temp!= participant; temp++)
            {
                time++;
                place++;
            }
            race_participants.Times.erase(time);
            race_participants.Places.erase(place);

            race_participants.Number_of_runners--;

            if(race_participants.Winner == participant->second)
                Declare_winner();
        }
        race_participants.Runners.erase(id);
    }
    else cout << "There is no participant with such id" << endl;

    if((finished) && (race_participants.Number_of_runners == 0))
    {
        cout << "The race is finished and has no participants, hence its going to be deleted" << endl;
        delete this;
    }
}

bool Race::Find_runner(const unsigned int id)
{
    if(race_participants.Runners.find(id)->first == id)
        return true;
    return false;
}

const Track* Race::Get_Where() const
{
    return Where;
}

const map<unsigned int, Member*> Race::Get_Participants() const
{
    return race_participants.Runners;
}

const unsigned int Race::get_id() const
{
    return Id;
}

const string Race::get_name() const
{
    return Name;
}

bool Race::Is_finished() const
{
    return finished;
}

void Race::operator=(Track& track)
{
    if(!finished)
    {
        Where->Remove_race(Id);
        Where = &track;

        Where->Add_race(*this);
    }
    else cout << "The race is finished and cannot be changed" << endl;
}

void Race::clear()
{
    for(auto& participant : race_participants.Runners)
    {
        participant.second->Remove_race(Id);
    }
    race_participants.Runners.clear();
    race_participants.Times.clear();
    race_participants.Places.clear();
    race_participants.Winner = nullptr;

    Where->Remove_race(Id);
    Where = nullptr;

    if(Which_League!= nullptr)
    {
        Which_League->Remove_race(Id);
        Which_League = nullptr;
    }
}

void Race::Calculate_average_time()
{
    double sum = 0;
    for(const auto& time : race_participants.Times)
    {
        sum += time;
    }
    race_participants.Average_time = sum / race_participants.Number_of_runners;
}

void Race::Assign_places()
{
    cout << "Input times: " << endl;

    string input;
    char *end;
    double temp;
    // Input of times of runners
    for(const auto& participant : race_participants.Runners)
    {
        cout << participant.second->get_name() << " " << participant.first << ": ";
        do
        {
            cin >> input;
            temp = strtod(input.c_str(), &end);

        } while (temp <= 0);
        
        race_participants.Times.push_back(temp);
    }

    vector<pair<double, unsigned int>> sorted_times;
    // Sorting of times in ascending order
    vector<double>::const_iterator time = race_participants.Times.begin();
    for(const auto& participant : race_participants.Runners)
    {
        sorted_times.push_back({*time, participant.first});
        time++;
    }
    sort(sorted_times.begin(), sorted_times.end());
    
    // Assigning places
    for(const auto& participant : race_participants.Runners)
    {
        int i = race_participants.Number_of_runners - 1;
        for(i; i >= 0; i--)
        {
            if(sorted_times[i].second == participant.first)
            {
                race_participants.Places.push_back(i + 1);
                break;
            }
        }
    }
}

void Race::Declare_winner()
{
    vector<unsigned int>::const_iterator place = race_participants.Places.begin();
    vector<double>::const_iterator time = race_participants.Times.begin();
    for(const auto& participant : race_participants.Runners)
    {
        if(*place == 1)
        {
            race_participants.Winner = participant.second;
            race_participants.Winner_time = *time;
            break;
        }
        place++;
        time++;
    }
}