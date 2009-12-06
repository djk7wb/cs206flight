#ifndef PERSON_H
#define PERSON_H

#include <iostream>

using namespace std;

class Group;

class Person
{
  public:
  void setName(string newName){name=newName;};
  string getName(){return name;};
  Group* getGroup(){return p_group;};

  private:
  Group* p_group;
  string name;

  friend class Group;
  friend class ReservationSys;
};

#endif

