
#include "Group.h"

int Group::nextID = 1;

Group::Group()
{
  groupID = nextID;
  nextID += 1;
  type = BUSINESS;
  smokingPreference = false;
  satisfaction = 0;
  numMembers = 0;
}

Group::Group(const Group& original)
{
  for (int i = 0; i < original.numMembers; i++)
  {
    addPerson(original.members[i]);
  }
  type = original.type;
  smokingPreference = original.smokingPreference;
  satisfaction = original.satisfaction;
  groupID = original.groupID;
}

Group& Group::operator=(const Group& original)
{
  for (int i = 0; i < original.numMembers; i++)
  {
    addPerson(original.members[i]);
  }
  type = original.type;
  smokingPreference = original.smokingPreference;
  satisfaction = original.satisfaction;
  groupID = original.groupID;
  return *this;
}

bool Group::addPerson(Person newPerson)
{
  newPerson.groupID = groupID;
  members[numMembers] = newPerson;
  numMembers++;
  return true;
}

