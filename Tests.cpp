#include "Association.h"

void Testing_adding_mountain_to_association(Association &Club)
{
	// Creatin a Mountain
	Mountain Temp = {"Tatry", "Poland", 2655};

	// Takes size before addig
	int size = Club.Get_mountaints_vector().size();

	// Ads a mountain
	Club.Add_Mountain(Temp);

	// Getting the vector of the mountains after adding
	const vector <Mountain*> Temp2 = Club.Get_mountaints_vector();

	// Checking size correctness
	if((size+1) != Temp2.size())
		cerr << "size is wrong after adding mountain";

	// Checking if the mountain is found in the vecotr
	const vector <Mountain*>::const_iterator Iterator = find(Temp2.begin(), Temp2.end(), Temp);

	if(*Iterator != &Temp)
		cerr << "The Mountain was not found";
}

void Testing_adding_member_to_association(Association &Club)
{
	// Creatin a Member
	Member Temp = {"Winnetou", 32, 'M', 1};

	// Takes size before addig
	int size = Club.Get_member_map().size();

	// Ads a Member to the Club
	unsigned int temp_id = Club.Add_Member(Temp);

	// Getting a map of the Members
	const map<unsigned int, Member*> Temp2 = Club.Get_member_map();

	// Checking size correctness
	if((size+1) != Temp2.size())
		cerr << "size is wrong after adding a member";

	// Checking if the Member is found in the map
	const map <unsigned int, Member*>::const_iterator Iterator = Temp2.find(temp_id);

	if(Iterator->second != &Temp)
		cerr << "The Member was not found";
}

void Testing_adding_track_to_association(Association &Club)
{
	// Creating a Track and assiging it a random Mountain
	Mountain *Temp_Mountain = *Club.Get_mountaints_vector().begin(); 
	Track Temp_Track("Red", *Temp_Mountain, 10.5, 7);

	// Getting size before adding
	int size = Club.Get_tracks_map().size();

	// Adding Track to the Club
	unsigned int temp_id = Club.Add_Track(Temp_Track);

	// Getting the tracks map
	const map<unsigned int, Track*> Temp2 = Club.Get_tracks_map();

	// Checking size correctness
	if((size+1) != Temp2.size())
		cerr << "size is wrong after adding a track";

	// Finding the iterator of the map with the new id
	const map <unsigned int, Track*>::const_iterator Iterator = Temp2.find(temp_id);

	// Checking if the Track is found in the map
	if(Iterator->second != &Temp_Track)
		cerr << "The Track was not found";

	// Checking wether the mountain has the pointer
	const map <unsigned int, Track*>::const_iterator Iterator = Temp_Mountain->mountains_tracks.find(temp_id);

	if(Iterator->second != &Temp_Track)
		cerr << "The Track was not found in the mountain";
}

void Testing_adding_race_to_association(Association &Club)
{
	// Getting size before adding
	int size = Club.Get_races_map().size();

	// Getting a random Track
	Track *Temp_Track = Club.Get_tracks_map().begin()->second;

	// Creating the Race
	Race Temp_Race("Happy new year run", Temp_Track);

	// Adding the Race
	unsigned int temp_id = Club.Add_Race();

	// Getting a map of the Races 
	const map<unsigned int, Race*> Temp_Race2 = Club.Get_races_map();

	// Checking size correctness
	if((size+1) != Temp_Race2.size())
		cerr << "size is wrong after adding a Race";

	// Checking if the Race is found in the map
	const map <unsigned int, Race*>::const_iterator Iterator = Temp_Race2.find(temp_id);

	if(Iterator->second != &Temp_Race)
		cerr << "The Race was not found";

	// Checking if the race can be found in the Temp_Track object
	if(Temp_Track->Get_Data().find(temp_id)->second != &Temp_Race)
		cerr << "The Race pointer was not found in the Track object";
}

void Testing_adding_league_to_association(Association &Club)
{
	// Getting size before adding
	int size = Club.Get_leagues_map().size();

	// Create an empty League
	League Temp_League("International League", "International League Trophy");

	// Add the League
	unsigned int temp_id = Club.Add_League(Temp_League);

	// Getting a map of the Leagues
	const map<unsigned int, League*> Temp2 = Club.Get_leagues_map();

	// Checking size correctness
	if((size+1) != Temp2.size())
		cerr << "size is wrong after adding a league";

	// Checking if the League is found in the map
	const map <unsigned int, League*>::const_iterator Iterator = Temp2.find(temp_id);

	if(Iterator->second != &Temp_League)
		cerr << "The League was not found";
}