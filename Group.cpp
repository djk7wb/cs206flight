
#include "Group.h"

int Group::nextID = 1;

Group::Group()
{
  groupID = nextID;
  nextID += 1;
  type = BUSINESS;
  smokingPreference = false;
  satisfaction = 0;
}

Group::Group(const Group& original)
{
  for (int i = 0; i < int(original.members.size()); i++)
  {
    addPerson(original.members[i]);
  }
  type = original.type;
  smokingPreference = original.smokingPreference;
  satisfaction = original.satisfaction;
  groupID = original.groupID;
}

bool Group::addPerson(Person newPerson)
{
  newPerson.groupID = groupID;
  members.push_back(newPerson);
  return true;
}

