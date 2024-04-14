#pragma once
#include <vector>
#include <iostream>
#include <string.h>
#include <map>
using namespace std;

class Member;
class Track;
class Race;
class League;

struct Mountain
{
	string Name;
	string Country;
	int elevation[2];
};

class association
{
    private:
		string Name;
        vector<Member> members;
        vector<Track> tracks;
        vector<Race> races;
		vector<League> leagues;
		vector<Mountain> mountains;
};

class Member
{
	friend association;
    private:
		unsigned int Id;
        string Name;
        int Age;
        char Gender;
        string Membership;
        long Performance_index;
		map<unsigned int, Race*>Participation;
        map<unsigned int, Track*>Best_times;
    public:
};

class Track
{
	friend association;
    struct Best
    {
        float time;
        Member* runner; 
    };
    private:
		unsigned int Id;
        string Name;
		Mountain *Where;
        long Difficulty;
		map<unsigned int, Race*>Schedule;
        double Average_time;
        Best Best_runner;
    public:
};

class Race
{
	friend association;
    private:
		unsigned int Id;
    public:
};

class League
{
	friend association;
    private:
		unsigned int Id;
};
