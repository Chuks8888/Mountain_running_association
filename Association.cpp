#include "Race.h"
#include "Track.h"
#include "Member.h"
#include "League.h"

Association::Association(string name)
{
    Name = name;
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