
#include "Group.h"

bool Group::addPerson(Person newPerson)
{
  newPerson.p_group = this;
  members.push_back(newPerson);
  return true;
}

