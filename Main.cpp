#include "Race.h"
#include "Track.h"
#include "Member.h"
#include "League.h"

unsigned int Race::Ids = 1;
unsigned int Track::Ids = 1;
unsigned int Member::Ids = 1;
unsigned int League::Ids = 1;

void MemberTest()
{
    // Create some objects to test with

    Mountain Tatry = {"Tatry", "Poland", 2655};
    Mountain Mount = {"Everest", "Nepal", 8848};

    Member Bob("Bob", 32, 'M');
    Member Alice("Alice", 28, 'F');
    Member John("John", 45, 'M');
    Member Sarah("Sarah", 35, 'F');
    Member David("David", 25, 'M');
    Member Emily("Emily", 38, 'F');

    Track Black("Black", Mount, 15, 10);
    Track Blue("Blue", Mount, 10, 7);
    Track White("White", Tatry, 12, 6);

	// those need to be made with new so that the program
	// does not try to delete the object twice
    Race *Marathon = new Race("Marathon", &White);
    Race HalfMarathon("Half Marathon", &Black);
    Race UltraMarathon("Ultra Marathon", &Blue);
    Race Relay("Relay", &White);
    
    League worldLeague("World League", "10k");

	 //Add the members to the league
	//worldLeague.Add_runner(Bob);
	//worldLeague.Add_runner(Alice);
	//worldLeague.Add_runner(John);
	//worldLeague.Add_runner(Sarah);
	//worldLeague.Add_runner(David);

	 //Add the races to the league
	worldLeague.Add_Race(*Marathon);
	//worldLeague.Add_Race(HalfMarathon);
	//worldLeague.Add_Race(UltraMarathon);

	//worldLeague.Start_League();

    //worldLeague.Add_runner(Emily);

	//worldLeague.Next_stage();
    //worldLeague.Next_stage();
    //worldLeague.Next_stage();

    //worldLeague.Remove_runner(Bob);

    //worldLeague.Get_winner()->Print();

    //Bob.Print();

    // Add members to non league races
	//Relay->Add_runner(Sarah);
    //Relay.Add_runner(David);
    


    /* Below are test for member class */

    
    // Test of destructors
    //auto& participants = Relay.Get_Participants();
    //auto& participants2 = worldLeague.Get_Runners();

    //David.~Member();
    //John.~Member();

    //if(Relay.Get_Participants().size() != 1)
    //{
        //cout << "Member was not removed from the race" << endl;
        //exit(1);
    //}

    //if(worldLeague.Get_Runners().size() != 2)
    //{
        //cout << "Member was not removed from the league" << endl;
        //exit(1);
    //}
    // end of test of destructors

    // Race functions in Member class

    //Emily.Add_race(Relay); // This should not work
    //if(Emily.Get_Participation().size() != 0)
    //{
        //cout << "The race was added despite limitations of the method";
        //exit(1);
    //}

    //Relay.Add_runner(Emily);

    //if(!Emily.Find_race(Relay))
    //{
        //cout << "The race was not found";
        //exit(1);
    //}

    //Emily.Remove_race(Relay);

    //if(Emily.Get_Participation().size() != 0)
    //{
        //cout << "The race was not removed";
        //exit(1);
    //}

    //if(Relay.Get_Participants().find(Emily.get_id())->first == Emily.get_id())
    //{
        //cout << "Emily was not removed from the race";
    //}
    
    //cerr << "All tests completed";

	//worldLeague.~League();

	//Sarah.Print();

}

int main()
{
    MemberTest();
}
