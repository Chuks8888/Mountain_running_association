#include "Race.h"
#include "Track.h"
#include "Member.h"
#include "League.h"
#include <ctype.h>
#include <cctype>

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
    chosen_id = 0;
}

Association::~Association()
{
    // Delets all leagues and its races
    for(auto& league : leagues)
    {
        delete league.second;
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

int Association::Add_Race()
{
    cout << "Creating a new race" << endl;

    cout << "Name: ";
    string name;
    cin >> name;

    Print_Tracks();
	unsigned int track_id;
    cout << "Select a Track: ";
	do
	{
		track_id = Decision(2, Track::Ids);
	}while(tracks.find(track_id) == tracks.end());
    Race *temp = new Race(name, *tracks.find(track_id)->second);
    races.insert({temp->Id, temp});

    chosen_id = temp->Id;
    return 1;
}

unsigned int Association::Add_League(League& league)
{
    leagues.insert({league.get_id(), &league});
    return league.get_id();
}

int Association::Add_League()
{
    cout << "Creating a new league" << endl;

    cout << "Name: ";
    string name;
    cin >> name;

    cin.ignore();

    cout << "Reward: ";
    string reward;
    cin >> reward;

    League *temp = new League(name, reward);
    leagues.insert({temp->Id, temp});

    chosen_id = temp->Id;
    return 2;
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
        cout << "\nWhat do you wish to edit?" << endl;
        cout << "Press any other key to go back" << endl;
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
                cout << "Press any other key to go back" << endl;
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

                    if(find_track && find_track->get_id() == selected_track)    
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
                cout << "Press any other key to go back" << endl;
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
                        if(find_member && selected_member == find_member->get_id())
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
                        cout << "Press any other key to go back" << endl;
                        do
                        {
                            race->Print();
                            cout << "Remove?: ";
                            selected_member = Decision(0, 0);

                            if(selected_member == 0)
                                break;

                            Member *find_member = members.find(selected_member)->second;
                            if(find_member && selected_member == find_member->get_id())
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
                    cout << "Press any other key to go back" << endl;
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
                        selected_member = Decision(0, 0);
                        if(race->race_participants.Runners.end() != race->race_participants.Runners.find(selected_member))
                        {
                            string new_time;
                            char *end;
                            double new_time_value;
                            do
                            {
								cout << "Iput new time: ";
                                cin >> new_time;
                                new_time_value = strtod(new_time.c_str(), &end);
                            } while (new_time_value <= 0);

							int i = 0;
							for(const auto& runner : race->race_participants.Runners)
							{
								if(runner.first == selected_member)
										break;
								i++;
							}

                            race->race_participants.Times[i] = new_time_value;
                            race->Assign_places();
                            race->Declare_winner();
                            race->Where->Finish_race(race->Id);

                            if(race->Which_League && race->Which_League->Get_status() == 2)
                                race->Which_League->Declare_winner();

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

int Association::Edit_League(unsigned int id)
{
    if(leagues.find(id) != leagues.end())
    {
        unsigned int input = 0;
        unsigned int select = 0;
        chosen_id = id;
        League *league = leagues.find(id)->second;

        cout << "League: " << league->Name << endl;
        cout << "League Id: " << league->Id << endl;
        for(const auto& race : league->Get_Races())
            cout << "Race: " << race.second->Name << "Id " << race.second->Id << endl;
        cout << "Participants: " << endl;
        for(const auto& member : league->Get_Runners())
            cout << "Runner: " << member.second->Name << "Id " << member.first << endl;
        
        cout << "What do you wish to edit: " << endl;
        cout << "Press any other key to go back" << endl;
        cout << "1. Name" << endl;
        cout << "2. Race" << endl;
        cout << "3. Member" << endl;
        cout << "4. Delete the league" << endl;
        if(!league->finished)
            cout << "5. Progress the league" << endl;
        cout << "Decision: ";
        input = Decision(0, league->finished ? 4 : 5);

        switch(input)
        {
            case 1:
            {
                string new_name;
                cout << "New name: ";
                cin >> new_name;
                league->Name = new_name;
                return 2;
            }
            case 2:
            {
                cout << "Do you wish to: " << endl;
                cout << "Press any other key to go back" << endl;
                cout << "1. Add a race" << endl;
                cout << "2. Remove a race" << endl;
                cout << "3. Edit a race" << endl;
                cout << "Decision: ";

                unsigned int decision1 = Decision(0, 3);
                if(decision1 == 0)
                    return 2;
                if(decision1 == 1)
                {
                    for(const auto& race : races)
                        cout << race.second->Name << "Id " << race.second->Id << endl;   
                    cout << "Press any other key to go back" << endl;
                    cout << "Add?: ";
                    select = Decision(0, 0);
                    if(select < 2)
                        return 2;
                    else if(races.find(select)->second)
                    {
                        league->Add_Race(*races.find(select)->second);
                        return 2;
                    }
                }

                for(const auto& race : league->Get_Races())
                        cout << race.second->Name << "Id " << race.second->Id << endl;
                    cout << "Press any other key to go back" << endl;

                if(decision1 == 2)
                {
                    cout << "Remove?: ";
                    select = Decision(0, 0);
                    if(select < 2)
                        return 2;
                    else
                    {
                        if(league->Get_Races().find(select) != league->Get_Races().end())
                        {
                            league->Remove_race(*races.find(select)->second);
                            races.erase(select);
                        }
                        return 2;
                    }
                }
                else
                {
                    cout << "Edit?: ";
                    select = Decision(0, 0);
                    if(select < 2)
                        return 2;
                    else
                    {
                        if(league->Get_Races().find(select) != league->Get_Races().end())
                        {
                            chosen_id = select;
                            return 1;
                        }
                        return 2;
                    }
                }
            }
            case 3:
            {
                cout << "Do you wish to: " << endl;
                cout << "Press any other key to go back" << endl;
                cout << "1. Add a runner" << endl;
                cout << "2. Remove a runner" << endl;
                cout << "3. Edit a runner" << endl;
                cout << "Decision: ";

                unsigned int decision1 = Decision(0, 3);
                if(decision1 == 0)
                    return 2;
                /* Add runners */
                if(decision1 == 1)
                {
                    if(members.empty())
                    {
                        cout << "There are no members" << endl;
                        return 2;
                    }
                    cout << endl;
                    Print_Members();
                    cout << "Press 0 to go back" << endl;
                    do
                    {
                        cout << "Add?: ";
                        select = Decision(0, 0);

                        if(select < 2)
                            break;

                        Member *find_member = members.find(select)->second;
                        if(find_member && select == find_member->get_id())
                            league->Add_runner(*find_member);
                        else
                            cout << "Member not found" << endl;
                    } while (select >= 2);
                    return 2;
                }
                for(const auto& member : league->Get_Runners())
                    cout << member.second->Name << " Id " << member.first << endl;
                cout << "Press any other key to go back" << endl;
                /* Remove Runners */
                if(decision1 == 2)
                {
                    if(!league->Get_Runners().empty())
                    {
                        do
                        {
                            cout << "Remove?: ";
                            select = Decision(0, 0);

                            if(select < 2)
                                break;

                            Member *find_member = members.find(select)->second;
                            if(find_member && select == find_member->get_id())
                                league->Remove_runner(*find_member);
                            else
                                cout << "Member not found" << endl;
                        } while (select >=2);
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

                    cout << "Edit?: ";

                    select = Decision(0, 0);

                    if(league->Get_Runners().find(select) != league->Get_Runners().end())
                    {
                        chosen_id = select;
                        return 3;
                    }
                    else
                    {
                        cout << "Member not found" << endl;
                        return 2;
                    }
                    return 2;
                }   
            }
            case 4:
            {
                cout << "Are you sure you want to delete the league? (y/n)" << endl;
                string decision1;
                cin >> decision1;
                if(decision1 == "y")
                {
                    for(const auto& race : league->League_Races)
                        races.erase(race.first);
                    delete league;
                    leagues.erase(id);
                }
                chosen_id = 0;
                return 0;
            }
            case 5:
            {
                cout << "Are you sure you want to progress the league? (y/n)" << endl;
                string decision1;
                cin >> decision1;
                if(decision1 == "y")
                {
                    if(league->In_progress)
                        league->Next_stage();
                    else league->Start_League();
                }
                return 2;
            }
        }
    }
    chosen_id = 0;
    return 0;
}

int Association::Edit_Member(unsigned int id)
{
    if(members.find(id) != members.end())
    {
        unsigned int input = 0;
        unsigned int select = 0;
        chosen_id = id;
        Member *member = members.find(id)->second;
        member->Print();

        cout << "Do you wish to: " << endl;
        cout << "Press any other key to go back" << endl;
        cout << "1. Change the name" << endl;
        cout << "2. Increase the age" << endl;
        cout << "3. Display/Edit Member's races" << endl;
        cout << "4. Remove the member from the association" << endl;
        cout << "Decision: ";
        input = Decision(0, 4);

        switch (input)
        {
            case 1:
            {
                string new_name;
                cout << "New name: ";
                cin >> new_name;
                member->Name = new_name;
                return 3;
            }
            case 2:
            {
                member->Age++;
                return 3;
            }
            case 3:
            {
                for(const auto &race : member->Get_Participation())
                    cout << race.second->Name << " Id: " << race.second->Id << endl;
                cout << "Press any other key to go back" << endl;
                cout << "Edit?: ";
                select = Decision(0, 0);
                if(select < 2)
                    return 3;
                else
                {
                    chosen_id = select;
                    return 1;
                }
            }
            case 4:
            {
                cout << "Are you sure you want to delete the member? (y/n)" << endl;
                string decision;
                cin >> decision;
                if(decision == "y")
                {
                    member->clear();
                    members.erase(id);
                    chosen_id = 0;
                    return 0;
                }
                return 3;
            }
            default:
            {
                chosen_id = 0;
                return 0;
            }
        }
    }
    chosen_id = 0;
    return 0;
}

int Association::Edit_Track(unsigned int id)
{
    if(tracks.find(id)!= tracks.end())
    {
        unsigned int input = 0;
        unsigned int select = 0;
        chosen_id = id;
        Track *track = tracks.find(id)->second;
        track->Print();

        cout << "Do you wish to: " << endl;
        cout << "Press any other key to go back" << endl;
        cout << "1. Change the name" << endl;
        cout << "2. Adjust the length" << endl;
        cout << "3. Increase the difficulty" << endl;
        cout << "4. Decrease the difficulty" << endl;
        if(!track->Get_Data().empty())
            cout << "5. Display/Edit Track's races" << endl;
        cout << "Decision: ";
        input = Decision(0, track->Get_Data().empty() ? 4 : 5);

        switch(input)
        {
            case 1:
            {
                string new_name;
                cout << "New name: ";
                cin >> new_name;
                track->Name = new_name;
                return 4;
            }
            case 2:
            {
                string input1;
                char *end;
                double length;

                cout << "1 Add" << endl;
                cout << "2 Subtract" << endl;
                cout << "Decision: ";
                if(Decision(1, 2) == 1)
                {
                    cout << "Value: ";
                    cin >> input1;
                    length = strtod(input1.c_str(), &end);
                    track->Length += length;
                }
                else
                {
                    cout << "Value: ";
                    cin >> input1;
                    length = strtod(input1.c_str(), &end);
                    track->Length -= length;
                }
                return 4;
            }
            case 3:
            {
                track->Difficulty++;
                return 4;
            }
            case 4:
            {
                track->Difficulty--;
                return 4;
            }
            case 5:
            {
                for(const auto &race : track->Get_Data())
                    cout << race.second->Name << " Id: " << race.second->Id << endl;
                cout << "Press any other key to go back" << endl;
                cout << "Edit?: ";
                select = Decision(0, Track::Ids);
                if(select < 2)
                    return 4;
                else
                {
                    chosen_id = select;
                    return 1;
                }
            }
            default:
                break;
        }
    }
    chosen_id = 0;
    return 0;
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
        if(league.second->Winner)
            cout << "Winner: " << league.second->Winner->Name << " Id: " << league.second->Winner->Id << endl;
        cout << "Reward: " << league.second->Reward << endl;
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
