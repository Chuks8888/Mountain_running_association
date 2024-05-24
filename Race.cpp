#include "Member.h"
#include "Race.h"
#include "Track.h"
#include "League.h"
#include <string>

Race::Race(string name, Track &where, League *which_League): Name(name), Where(&where), Which_League(which_League)
{
   Id = Ids;
   Ids++;

   finished = false;

   race_participants.Number_of_runners = 0;
   race_participants.Winner =  nullptr;

   if (which_League!= nullptr)
   {
      which_League->Add_Race(*this);
   }

   where.Add_race(*this);
}

Race::~Race()
{
	if(!this)
		return;
    clear();
    cerr << "Race " << Name << " deleted" << endl;
}

void Race::Print() const
{   
    cout << "\nRace name: " << Name << endl << "Race Id: " << get_id() << endl;
    cout << "Track name: " << Where->Get_Name() << endl << "Track Id: " << Where->get_id() << endl;
    if(Which_League!= nullptr)
        cout << "League: " << Which_League->Get_Name() << " Id: " << Which_League->get_id() << endl;

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
    if(Which_League && Which_League->Get_status() == 0)
    {
        cout << "The league is not started" << endl;
        return;
    }

    if(race_participants.Number_of_runners != 0)
    {
        Input_times();
        Assign_places();
        Declare_winner();

        finished = true;
        Where->Finish_race(Id);

        for(const auto& participant : race_participants.Runners)
            participant.second->Calculate_performance();

        cerr << "Race " << Name << " " << Id << " finished" << endl;
    }
    else
        cout << "There are no participants in the race" << endl;
}

double Race::Get_Average_time() const
{
    if(finished) return race_participants.Average_time;
	return 0.0;
}

double Race::Get_Winner_time() const
{
    if(finished) return race_participants.Winner_time;
	return 0.0;
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
    return race_participants.Winner;
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
            cout << participant.get_name() << " added to the race " << Name << endl;
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
    participant.Remove_race(Id);
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
            for(map<unsigned int, Member*>::const_iterator temp = race_participants.Runners.begin(); temp->first != participant-> first; temp++)
                ++time;

            race_participants.Times.erase(time);
            race_participants.Places.clear();

            race_participants.Number_of_runners--;
            race_participants.Runners.erase(id);

            Assign_places();
            Declare_winner();
            Where->Finish_race(Id);
        }
        else race_participants.Runners.erase(id);
    }

    if((finished) && (race_participants.Runners.empty()))
    {
        finished = false;
    }
}

bool Race::Find_runner(const unsigned int id)
{
    if(race_participants.Runners.find(id) != race_participants.Runners.end())
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
    if(true)
    {
        Where->Remove_race(Id);
        Where = &track;

        Where->Add_race(*this);
        if(finished)
            Where->Finish_race(Id);
    }
    else cout << "The race is finished and cannot be changed" << endl;
}

void Race::clear()
{

    if(Which_League!= nullptr)
    {
        Which_League->Remove_race(Id);
        return;
    }
	else
	{
		Where->Remove_race(Id);
		Where = nullptr;

		for(auto& participant : race_participants.Runners)
		{
			participant.second->Remove_race(Id);
		}
		race_participants.Runners.clear();
		race_participants.Winner = nullptr;
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

void Race::Input_times()
{
	cout << Name << " Id: " << Id;
    cout << "\nInput times: " << endl;

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
}

void Race::Assign_places()
{
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
        int i = race_participants.Runners.size() - 1;
        for(i; i >= 0; i--)
        {
            if(sorted_times[i].second == participant.first)
            {
                race_participants.Places.push_back(i + 1);
                break;
            }
        }
    }
    Calculate_average_time();
}

void Race::Declare_winner()
{
    if(race_participants.Number_of_runners == 0)
    {
        race_participants.Winner = nullptr;
    }
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
