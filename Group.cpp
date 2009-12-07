
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
  groupID = original.groupID;
  for (int i = 0; i < (int)original.members.size(); i++)
  {
    addPerson(*(original.members[i]));
  }
  type = original.type;
  smokingPreference = original.smokingPreference;
  satisfaction = original.satisfaction;
}

Group::~Group()
{
  for (int i=0; i < (int)members.size(); i++)
  {
    delete members[i];
  }
}

bool Group::addPerson(Person newPerson)
{
  Person *tmpPerson = new Person;
  tmpPerson->groupID = groupID;
  tmpPerson->name = newPerson.name;
  tmpPerson->row = newPerson.row;
  tmpPerson->col = newPerson.col;
  members.push_back(tmpPerson);
  return true;
}

