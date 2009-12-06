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
  int getRow(){return row;};
  int getCol(){return col;};

  private:
  Group* p_group;
  string name;
  int row;
  int col;

  friend class Group;
  friend class ReservationSys;
};

#endif

