
#ifndef GROUP_H
#define GROUP_H

#include <vector>

using namespace std;

#include "Person.h"

enum GroupType
{
  FAMILY,
  TOURISTS,
  BUSINESS
};

class Group
{
  public:
  bool addPerson(Person);
  GroupType type;
  bool smokingPreference;
  int satisfaction;

  private:
  vector<Person> members;

  friend class ReservationSys;
};

#endif

