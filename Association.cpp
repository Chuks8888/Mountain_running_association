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