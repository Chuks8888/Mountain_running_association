#include "Race.h"
#include "Track.h"
#include "Member.h"
#include "League.h"

unsigned int Race::Ids = 2;
unsigned int Track::Ids = 2;
unsigned int Member::Ids = 2;
unsigned int League::Ids = 2;

void Tests()
{
    // Create some objects to test with

    /* Mountiants */
    Mountain Tatry = {"Tatry", "Poland", 2655};
    Mountain Mount = {"Everest", "Nepal", 8848};

    /* Members */
    Member Emily("Emily", 38, 'F');
    Member Bob("Bob", 32, 'M');
    Member Alice("Alice", 28, 'F');
    Member *John = new Member("John", 45, 'M'); // will be deleted
    Member Sarah("Sarah", 35, 'F');
    Member *David = new Member("David", 25, 'M'); // will be deleted

    /* Tracks */
    Track Black("Black", Mount, 15, 10);
    Track Blue("Blue", Mount, 10, 7);
    Track White("White", Tatry, 12, 6);

    /* Races */
    Race Relay("Relay", &Blue);
	Race *Money = new Race("Money", &Black);
    Race *Marathon = new Race("Marathon", &White);

    /* Leagues */
    League worldLeague("worldLeague", "Trophy");

    // Add members to non league races
    Relay.Add_runner(Bob);
    Relay.Add_runner(*David);

    // Add Members to league
    worldLeague.Add_Race(*Marathon);
	worldLeague.Add_Race(*Money);
    worldLeague.Add_runner(*John);
    worldLeague.Add_runner(Sarah);
    worldLeague.Add_runner(Alice);
    
    /*                       */
    /* Start of Member tests */
    /*                       */
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
	cerr << "End of member tests\n";
    /*                     */
    /* End of Member tests */
    /*                     */
}

int main()
{
    Tests();
    cout << "\nAll test complete\n";
}
