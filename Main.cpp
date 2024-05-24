#include "Race.h"
#include "Member.h"
#include "Track.h"
#include "League.h"
#include "Tests.h"

void Countinue()
{
    cout << "Press any key to continue..." << endl;
    cin.ignore();
    cin.ignore();
}

// uncomment the test in order to do the unit tests
//#define TEST

#define check 0

#ifdef TEST
#define check 1
#endif

int main()
{
    if(check)
	{
        Tests();
	}
    // defining the Association
    Association association("MRA");

    /* Here you can define the Association Members */
    Member member1("John", 30, 'M', 2); association.Add_Member(member1);
    Member member2("Jane", 28, 'F'); association.Add_Member(member2);
    Member member3("Michael", 35, 'M', 2); association.Add_Member(member3);
    Member member4("Emily", 25, 'F'); association.Add_Member(member4);
    Member member5("David", 32, 'M', 2); association.Add_Member(member5);
    Member member6("Sarah", 29, 'F'); association.Add_Member(member6);
    Member member7("Andrew", 31, 'M', 2); association.Add_Member(member7);
    Member member8("Olivia", 27, 'F'); association.Add_Member(member8);
    Member member9("Matthew", 33, 'M', 2); association.Add_Member(member9);
    Member member10("Christopher", 26, 'M'); association.Add_Member(member10);
    /* END OF DEFINING MEMBERS */

    /* Here you can define the Mountains*/
    Mountain Tatry = {"Tatry", "Poland", 2655}; association.Add_Mountain(Tatry);
    Mountain Mount = {"Everest", "Nepal", 8848}; association.Add_Mountain(Mount);
    Mountain Kilimanjaro = {"Kilimanjaro", "Tanzania", 5895}; association.Add_Mountain(Kilimanjaro);
    /* END OF DEFINING MOUNTAINS */

    /* Here you can define Tracks */
    Track track1("Tatry 1", Tatry, 10, 5); association.Add_Track(track1);
    Track track2("Tatry 2", Tatry, 12, 6); association.Add_Track(track2);
    Track track3("Tatry 3", Tatry, 15, 7); association.Add_Track(track3);

    Track track4("Everest 1", Mount, 10, 9); association.Add_Track(track4);
    Track track5("Everest 2", Mount, 12, 10); association.Add_Track(track5);
    Track track6("Everest 3", Mount, 15, 4); association.Add_Track(track6);

    Track track7("Kilimanjaro 1", Kilimanjaro, 10, 8); association.Add_Track(track7);
    Track track8("Kilimanjaro 2", Kilimanjaro, 12, 6); association.Add_Track(track8);
    Track track9("Kilimanjaro 3", Kilimanjaro, 15, 7); association.Add_Track(track9);
    /* END OF DEFINING TRACKS */

    unsigned int input = 0;
    unsigned int select = 0;
    unsigned int returned = 0;
    do
    {
        cout << endl;
        if(association.chosen_id == 0)
        {
            cout << "1. Create a race" << endl;
            cout << "2. Create a league" << endl;
            cout << "3. Edit/Display Races" << endl;
            cout << "4. Edit/Display Leagues" << endl;
            cout << "5. Show finished Races" << endl;
            cout << "6. Show future Races" << endl;
            cout << "7. Display/Edit Members" << endl;
            cout << "8. Display/Edit Tracks" << endl;
            cout << "Press any other key to exit" << endl;
            cout << "Enter your choice: ";
            input = Decision(0, 8);
        
            switch(input)
            {
                case 1:
                {
                    returned = association.Add_Race();
                    break;
                }
                case 2:
                {
                    returned = association.Add_League();
                    break;
                }
                case 3:
                {
                    association.Print_All_Races();
                    cout << "\nSelect a race: ";
                    select = Decision(0, 0);
                    returned = association.Edit_Race(select);
                    break;
                }
                case 4:
                {
                    association.Print_Leagues();
                    cout << "\nSelect a league: ";
                    select = Decision(0, 0);
                    returned = association.Edit_League(select);
                    break;
                }
                case 5:
                {
                    association.Print_Finished_Races();
                    Countinue();
                    break;
                }
                case 6:
                {
                    association.Print_Unfinished_Races();
                    Countinue();
                    break;
                }
                case 7:
                {
                    association.Print_Members();
                    cout << "\nSelect a member: ";
                    select = Decision(0, 0);
                    returned = association.Edit_Member(select);
                    break;
                }
                case 8:
                {
                    association.Print_Tracks();
                    cout << "\nSelect a track: ";
                    select = Decision(0, 0);
                    returned = association.Edit_Track(select);
                    break;
                }
                default:
                {
                    input = 0;
                }
            }
        }
        switch (returned)
        {
            case 1:
            {
                returned = association.Edit_Race(association.chosen_id);
                break;
            }
            case 2:
            {
                returned = association.Edit_League(association.chosen_id);
                break;
            }
            case 3:
            {
                returned = association.Edit_Member(association.chosen_id);
                break;
            }
            case 4:
            {
                returned = association.Edit_Track(association.chosen_id);
                break;
            }
            default:
                association.chosen_id = 0;
        }
    }
    while(input != 0);
    return 0;
}
