
#include "ReservationSys.h"

using namespace std;

int main()
{
  ReservationSys testSys;
  cout << testSys << endl;
  Group testGroup;
  Person testPerson;
  testGroup.type = BUSINESS;
  testGroup.addPerson(testPerson);
  testGroup.smokingPreference = true;
  testSys.addGroup(testGroup);
  cout << testSys << endl;
  return 0;
}

