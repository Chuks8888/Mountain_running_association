#include "Race.h"
#include "Track.h"
#include "Member.h"
#include "League.h"

unsigned int Decision(int lower, int upper)
{
    string decision;
    char* end;
    int choice;

    do
    {
        cin >> decision;
        choice = strtol(decision.c_str(), &end, 10);

    } while ((lower == upper)? (choice < lower) : (choice < lower || choice > upper));

    return choice;
}

Association::Association(string name)
{
    Name = name;
    cout << Decision(0, 5) << endl;
}

Association::~Association()
{
    // Delets all leagues and its races
    for(auto& league : leagues)
    {
        delete league.second;
    }

    // deletes all tracks and races that are there
    for(auto& track : tracks)
    {
        delete track.second;
    }

    for(auto& member : members)
    {
        delete member.second;
    }

    for(auto& mountain : mountains)
    {
        delete mountain;
    }

    leagues.clear();
    tracks.clear();
    members.clear();
    mountains.clear();
    races.clear();

    cout << "Association " << Name << " deleted" << endl;
}

unsigned int Association::Add_Member(Member& member)
{
    members.insert({member.get_id(), &member});
    return member.get_id();
}

unsigned int Association::Add_Track(Track& track)
{
    tracks.insert({track.get_id(), &track});
    return track.get_id();
}

unsigned int Association::Add_Race(Race& race)
{
    races.insert({race.get_id(), &race});
    return race.get_id();
}

unsigned int Association::Add_League(League& league)
{
    leagues.insert({league.get_id(), &league});
    return league.get_id();
}

void Association::Add_Mountain(Mountain& mountain)
{
    mountains.push_back(&mountain);
}

int Association::Edit_Race(unsigned int id)
{
    Race* race = races.find(id)->second;
    if(race == nullptr || race->get_id() != id) 
    {
        cout << "Race not found" << endl;
        return 0;
    }
    else
    {
        chosen_id = id;
        race->Print();
        cout << "\nWhat do you want to edit?" << endl;
        cout << "0. Go back to main menu" << endl;
        cout << "1. Name" << endl;
        cout << "2. Track" << endl;
        cout << "3. Runners" << endl;
        cout << "4. Delete the race" << endl;
        if(race->finished == false)
                cout << "5. Finish the race" << endl;

        cout << "Decision: "; 
        int decision;
        decision = Decision(0, (race->finished ? 4 : 5));

        switch(decision)
        {
            /* Go back */
            case 0:
            {
                chosen_id = 0;
                return 0;
            }
            /* Edit tht name */
            case 1:
            {
                cout << "New name: ";
                string name;
                cin >> name;
                race->Name = name;
                return 1;
            }
            /* Edit the track */
            case 2:
            {
                cout << "Do you wish to: " << endl;
                cout << "Press 0 to go back" << endl;
                cout << "1. Change the track" << endl;
                cout << "2. Eddit the current track" << endl;
                cout << "Decision: ";
                unsigned int decision1 = Decision(0, 2);

                /* go back */
                if(decision1 == 0)
                {
                    return 1;
                }
                /* Change the track */
                if(decision1 == 1)
                {
                    cout << endl;
                    Print_Tracks();
                    cout << endl << "Decision: ";

                    unsigned int selected_track = Decision(0,0);
                    
                    Track *find_track = tracks.find(selected_track)->second;

                    if(find_track->get_id() == selected_track)    
                        *race = *find_track;
                    else
                    {
                        cout << "Track not found" << endl;
                        return 1;
                    }
                }
                /* Edit the current track */
                else
                {
                    chosen_id = race->Where->get_id();
                    return 4;
                }
                break;
            }
            /* Edit the runners */
            case 3:
            {
                cout << "Do you wish to: " << endl;
                cout << "Press 0 to go back" << endl;
                cout << "1. Add a runner" << endl;
                cout << "2. Remove a runner" << endl;
                cout << "3. Edit a runner (time and runner)" << endl;
                cout << "Decision: ";

                unsigned int decision1 = Decision(0, 3);
                unsigned int selected_member;

                /* Add runners */
                if(decision1 == 1)
                {
                    if(members.empty())
                    {
                        cout << "There are no members" << endl;
                        return 1;
                    }
                    cout << endl;
                    Print_Members();
                    cout << "Press 0 to go back" << endl;
                    do
                    {
                        cout << "Add?: ";
                        selected_member = Decision(0, 0);

                        if(selected_member == 0)
                            break;

                        Member *find_member = members.find(selected_member)->second;
                        if(selected_member == find_member->get_id())
                            race->Add_runner(*find_member);
                        else
                            cout << "Member not found" << endl;
                    } while (selected_member != 0);
                    return 1;
                }
                /* Remove Runners */
                if(decision1 == 2)
                {
                    if(!race->race_participants.Runners.empty())
                    {
                        cout << "Press 0 to go back" << endl;
                        do
                        {
                            race->Print();
                            cout << "Remove?: ";
                            selected_member = Decision(0, 0);

                            if(selected_member == 0)
                                break;

                            Member *find_member = members.find(selected_member)->second;
                            if(selected_member == find_member->get_id())
                                race->Remove_runner(*find_member);
                            else
                                cout << "Member not found" << endl;
                        } while (selected_member != 0);
                    }
                    else 
                        cout << "There are no runners" << endl;
                    return 1;
                }
                /* Edit runners */
                else
                {
                    if(members.empty())
                    {
                        cout << "There are no members" << endl;
                        return 1;
                    }

                    cout << "Do you wish to: " << endl;
                    cout << "Press 0 to go back" << endl;
                    cout << "1. Change the time" << endl;
                    cout << "2. Edit the runner" << endl;
                    cout << "Decision: ";

                    unsigned int decision2 = Decision(0, 2);
                    /* Edit the time */
                    if(decision2 == 1)
                    {
                        if(!race->finished)
                        {
                            cout << "The race is not finished" << endl;
                            return 1;
                        }
                        race->Print();
                        cout << "Change the time of: ";
                        selected_member = Decision(0,0);
                        if(selected_member == race->race_participants.Runners.find(selected_member)->first)
                        {
                            string new_time;
                            char *end;
                            double new_time_value;
                            do
                            {
                                cin >> new_time;
                                new_time_value = strtod(new_time.c_str(), &end);
                            } while (new_time_value > 0);

                            race->race_participants.Times[selected_member-2] = new_time_value;
                            race->Assign_places();
                            race->Declare_winner();
                            race->Where->Finish_race(race->Id);
                            return 1;
                        }
                    }
                    /* Edit the runner */
                    if(decision2 == 2)
                    {
                        race->Print();
                        cout << "Edit the runner: ";
                        selected_member = Decision(0,0);
                        if(selected_member == race->race_participants.Runners.find(selected_member)->first)
                        {
                            chosen_id = selected_member;
                            return 3;
                        }
                        else
                        {
                            cout << "Member not found" << endl;
                            return 1;
                        }
                    }
                    /* go back */
                    return 1;

                }
            }
            /* Delete the Race */
            case 4:
            {
                cout << "Are you sure you want to delete the race? (y/n)" << endl;
                string decision1;
                cin >> decision1;
                if(decision1 == "y")
                {
                    delete race;
                    races.erase(id);
                }
                break;
            }
            /* Finish the race */
            case 5:
            {
                race->Finish_race();
                return 1;
            }
            default: break;
        }
        chosen_id = 0;
        return 0;
    }
}

int Association::Print_Unfinished_Races() const
{
	int i = 0;
    for(const auto &race : races)
    {
        if(!race.second->finished)
        {
            cout << race.second->Name << " Id: " << race.second->Id << endl;
			i++;
        }
    }
	return i;
}

int Association::Print_Finished_Races() const
{
	int i = 0;
    for(const auto &race : races)
    {
        if(race.second->finished)
        {
			i++;
            cout << race.second->Name << " Id: " << race.second->Id << endl;
        }
    }
	return i;
}

int Association::Print_All_Races() const
{
	int i = 0;
    for(const auto &race : races)
    {
		i++;
        cout << race.second->Name << " Id: " << race.second->Id << endl;
    }
	return i;
}

void Association::Print_Members() const
{
    for(const auto &member : members)
    {
        cout << member.second->Name << " Id: " << member.second->Id << endl;
    }
}

void Association::Print_Tracks() const
{
    for(const auto &track : tracks)
    {
        cout << track.second->Name << " Id: " << track.second->Id << endl;
    }
}

void Association::Print_Leagues() const
{
    for(const auto &league : leagues)
    {
        cout << league.second->Name << " Id: " << league.second->Id << endl;
        cout << "Reward: " << league.second->Reward << endl;
        for(const auto &race: league.second->League_Races)
        {
            cout << race.second->Name << " Id: " << race.second->Id << endl;
        }
        cout << "Runners: " << endl;
        for(const auto &member: league.second->League_Runners)
        {
            cout << member.second->Name << " Id: " << member.second->Id << endl;
        }
    }
}

void Association::Print_Mountains() const
{
    cout << "Mountains: " << endl;
    for(const auto &mountain : mountains)
    {
        cout << "Name: " << mountain->Name;
        cout << "Place: " << mountain->Country;
        cout << "Height: " << mountain->Height << endl;
        for(const auto &track : mountain->mountains_tracks)
        {
            cout << "Track: " << track.second->Name << " Id: " << track.second->Id << endl;
        }
    }
}

map<unsigned int, Member*> Association::Get_member_map() const
{
    return members;
}

map<unsigned int, Track*> Association::Get_tracks_map() const
{
    return tracks;
}

map<unsigned int, Race*> Association::Get_races_map() const
{
    return races;
}

map<unsigned int, League*> Association::Get_leagues_map() const
{
    return leagues;
}

vector<Mountain*> Association::Get_mountaints_vector() const
{
    return mountains;
} 
