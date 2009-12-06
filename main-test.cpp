
#include "ReservationSys.h"

using namespace std;

int main()
{
  ReservationSys testSys;
  vector<Group> allGroups;
  Person testPerson;
  testPerson.setName("Joe Miner");
  int input;

  do
  {
    cout << testSys << endl;
    cout << "New group size (-1 to quit) : ";
    cin >> input;

    allGroups.push_back(Group());
    if (input == 1)
    {
      allGroups.back().type = BUSINESS;
      allGroups.back().smokingPreference = true;
    }
    else if (input == 2)
    {
      allGroups.back().type = TOURISTS;
    }
    else
    {
      allGroups.back().type = FAMILY;
    }

    for (int i = 0; i < input; i++)
    {
      allGroups.back().addPerson(testPerson);
    }

    if (input != -1)
    {
      testSys.addGroup(allGroups.back());
    }

  }while(input != -1);

  return 0;
}

