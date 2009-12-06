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
  Group();
  Group(const Group& original);
  Group& operator=(const Group& other);

  bool addPerson(Person newPerson);
  GroupType type;
  bool smokingPreference;
  int satisfaction;
  int groupID;
  static int nextID;
  bool toTicket();
  Person* getMembers(){return members;};
  int getNumMembers(){return numMembers;};

  private:
  Person members[5];
  int numMembers;

  friend class ReservationSys;
};

#endif

