#include "Race.h"
#include "Track.h"
#include "Member.h"
#include "League.h"

unsigned int Race::Ids = 2;
unsigned int Track::Ids = 2;
unsigned int Member::Ids = 2;
unsigned int League::Ids = 2;

void MemberTests()
{
    // Create some objects to test with

    /* Mountiants */
    Mountain Tatry = {"Tatry", "Poland", 2655};
    Mountain Mount = {"Everest", "Nepal", 8848};

    /* Members */
    Member Emily("Emily", 38, 'F');
    Member Bob("Bob", 32, 'M');
    Member Alice("Alice", 28, 'F');
    Member Sarah("Sarah", 35, 'F');
    Member *John = new Member("John", 45, 'M');
    Member *David = new Member("David", 25, 'M');

    /* Tracks */
    Track Black("Black", Mount, 15, 10);
    Track Blue("Blue", Mount, 10, 7);
    Track White("White", Tatry, 12, 6);

    /* Races */
    Race Relay("Relay", Blue);
	Race *Money = new Race("Money", Black);
    Race *Marathon = new Race("Marathon", White);

    /* Leagues */
    League worldLeague("worldLeague", "Trophy");
    worldLeague.Add_Race(*Marathon);
	worldLeague.Add_Race(*Money);

    // Add members to non league races
    Relay.Add_runner(Bob);
    Relay.Add_runner(*David);

    // Add Members to league
    worldLeague.Add_runner(*John);
    worldLeague.Add_runner(Sarah);
    worldLeague.Add_runner(Alice);

    auto& participants = Relay.Get_Participants();
    delete David;
    delete John;

    if(Relay.Get_Participants().size() != 1)
    {
        cout << "John was not removed from the race" << endl;
        exit(1);
    }

    if(worldLeague.Get_Runners().size() != 2)
    {
        cout << "David was not removed from the league" << endl;
        exit(1);
    }

    // Test of Race methods that use the methods in Member class
    Emily.Add_race(Relay); // This should not work
    if(Emily.Get_Participation().size() != 0)
    {
        cout << "The race was added despite limitations of the method";
        exit(1);
    }

    Relay.Add_runner(Emily);

    if(!Emily.Find_race(Relay))
    {
        cout << "The race was not found";
        exit(1);
    }

    Emily.Remove_race(Relay);

    if(Emily.Get_Participation().size() != 0)
    {
        cout << "The race was not removed";
        exit(1);
    }

    if(Relay.Get_Participants().find(Emily.get_id())->first == Emily.get_id())
    {
        cout << "Emily was not removed from the race";
        exit(1);
    }
    cerr << endl << "End of member tests\n" << endl;
}

void TrackTests()
{
    // Create a mountain
    Mountain Tatry = {"Tatry", "Poland", 2655};
    // Create a Track obejct
    Track Path("Path", Tatry, 12, 6);

    // Test of construction
    // The mountain should add the track to itself
    if(Tatry.mountains_tracks.find(Path.get_id())->first!= Path.get_id())
    {
        cerr << "The track was not added to the mountain";
        exit(1);
    }

    // Create some more objects
    Track *White = new Track("White", Tatry, 13);
    Member Bob("Bob", 32, 'M');
    League worldLeague("worldLeague", "Trophy");
    Race *Marathon = new Race("Marathon", *White);
    worldLeague.Add_Race(*Marathon);
    worldLeague.Add_runner(Bob);

    // Test if The race was added to the track
    // after the construction of the race
    if(White->Get_Data().size() != 1)
    {
        cerr << "The race was not added to the track";
        exit(1);
    }

    // Test of destruction
    delete White;

    // After the destruction of the track the race should be removed
    if(worldLeague.Get_Races().size() != 0)
    {
        cerr << "The race was not removed during track destruction";
        exit(1);
    }

    // After the destruction of the race the member should be removed
    if(Bob.Get_Participation().size() != 0)
    {
        cerr << "The member was not removed during track destruction";
        exit(1);
    }

    // Create more objects
    Race Money("Money", Path);
    Race *Omega = new Race("Omega", Path);
    Member Alice("Alice", 28, 'F');
    Money.Add_runner(Alice);
    Money.Add_runner(Bob);
    Omega->Add_runner(Alice);
    Omega->Add_runner(Bob);

    // Test if the finished races influence the 
    // Track parameters
    // Please input respectively
    cerr << "\n!!!Please input respectively 4, 3, 2, 1 in order to get correct test results!!!" << endl;
    Money.Finish_race();
    Omega->Finish_race();

    if(Path.get_average_time() != 2.5)
    {
        cerr << "The average time was not calculated correctly";
        exit(1);
    }

    if(Path.Get_Best_time().first!= 1)
    {
        cerr << "The best time was not calculated correctly";
        exit(1);
    }

    // See if deleting the race and removing a runner causes anything
    delete Omega;

    if(Path.get_average_time() != 3.5)
    {
        cerr << "The average time after deleting a race was not calculated correctly";
        exit(1);
    }

    if(Path.Get_Best_time().first!= 3)
    {
        cerr << "The best time after deleting a race was not calculated correctly";
        exit(1);
    }

    Alice.Remove_race(Money);

    if(Path.get_average_time() != 4)
    {
        cerr << "The average time after deleting a runner was not calculated correctly";
        exit(1);
    }

    if(Path.Get_Best_time().first!= 4)
    {
        cerr << "The best time after deleting a runner was not calculated correctly";
        exit(1);
    }
    cerr << endl <<  "End of track tests\n" << endl;
}

int main()
{
    MemberTests();
    TrackTests();
    cout << "\nAll test complete\n" ;
}
