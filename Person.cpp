
#include "Person.h"

Person::Person()
{
  groupID = -1;
  name = "Not Named";
  row = -1;
  col = -1;
}

Person::Person(const Person& other)
{
  groupID = other.groupID;
  name = other.name;
  row = other.row;
  col = other.col;
}

Person& Person::operator=(const Person& other)
{
  groupID = 1; //other.groupID;
  name = other.name;
  row = other.row;
  col = other.col;
  return *this;
}
