
#include "Person.h"

Person::Person()
{

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
  groupID = other.groupID;
  name = other.name;
  row = other.row;
  col = other.col;
  return *this;
}
