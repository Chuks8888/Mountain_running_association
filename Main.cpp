#include "Race.h"
#include "Track.h"
#include "Member.h"
#include "League.h"

unsigned int Race::Ids = 1;
unsigned int Track::Ids = 1;
unsigned int Member::Ids = 1;
unsigned int League::Ids = 1;


int main()
{
    Mountain Mount = {"Everest", "Nepal", 8848};

    Member Bob("Bob", 32, 'M');
    Member Alice("Alice", 28, 'F');
    Member John("John", 45, 'M');
    Member Sarah("Sarah", 35, 'F');
    Member David("David", 25, 'M');
    Member Emily("Emily", 38, 'F');

    Bob.Gold_membership();
    ++Bob;

    Track White("White", Mount, 12, 9);

    Race Tour("Tour", &White);

    Tour.Add_runner(Bob);
    Tour.Add_runner(Alice);
    Tour.Add_runner(John);
    Tour.Add_runner(Sarah);
    Tour.Add_runner(David);
    Tour.Add_runner(Emily);

    Bob.Remove_race(Tour);
    Bob.Print();

    Tour.Finish_race();
    Tour.Print();

    White.~Track();
    Bob.~Member();
}