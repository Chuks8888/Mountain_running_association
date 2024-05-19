#include "Member.h"
#include "Race.h"
#include "Track.h"
#include "League.h"

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

    Race Marathon("Marathon", &White);
    Race HalfMarathon("Half Marathon", &Black);
    Race UltraMarathon("Ultra Marathon", &Blue);
    Race Relay("Relay", &White);
    
    League worldLeague("World League", "10k");

    // Add the members to the league
    worldLeague.Add_runner(Bob);
    worldLeague.Add_runner(Alice);
    worldLeague.Add_runner(John);

    // Add the races to the league
    worldLeague.Add_Race(Marathon);
    worldLeague.Add_Race(HalfMarathon);
    worldLeague.Add_Race(UltraMarathon);

    // Add members to non league races
    Relay.Add_runner(Sarah);
    Relay.Add_runner(David);

    // Test of destructors
    David.~Member();
    John.~Member();

    auto& participants = Relay.Get_Participants();
    auto& participants2 = worldLeague.Get_Runners();

    if(participants.size() != 1)
    {
        cout << "Member was not removed from the race" << endl;
        exit(1);
    }

    if(participants2.size() != 2)
    {
        cout << "Member was not removed from the league" << endl;
        exit(1);
    }

}