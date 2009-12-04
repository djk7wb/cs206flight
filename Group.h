
#include <vector>

using namespace std;

class Person;

enum GroupType
{
  FAMILY,
  TOURISTS,
  BUSINESS
};

class Group
{
  GroupType type;
  bool smokingPreference;
  int satisfaction;
  vector<Person> members;
};


