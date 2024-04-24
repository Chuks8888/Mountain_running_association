#include "Association.h"

void Testing_adding_to_association(Association &Club)
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
	if(*Iterator != &Temp )
		cerr << "The Mountain was not found";
}
