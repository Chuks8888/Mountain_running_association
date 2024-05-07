#include "Association.h"

unsigned int Track::Ids = 0;

Track::Track(string name, Mountain mountain, int length, unsigned int difficulty)
{
	Id = Ids;
	Ids ++;

	Name = name;
	Where = &mountain;
	Difficulty = difficulty;
	Length = length;

	Average_time = 0.0;
	Best_time.runner = nullptr;
	Best_time.time = 0.0;
}

        
