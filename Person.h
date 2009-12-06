#ifndef PERSON_H
#define PERSON_H

#include <iostream>

using namespace std;

class Group;

class Person
{
  public:
  Person();
  Person(const Person& other);
  Person& operator=(const Person& other);
  void setName(string newName){name=newName;};
  string getName(){return name;};
  //Group* getGroup(){return p_group;}; Use ReservationSys::getGroup(int,int)
  int getRow(){return row;};
  int getCol(){return col;};

  private:
  //Group* p_group; //Removed in favor of groupID
  int groupID;
  string name;
  int row;
  int col;

  friend class Group;
  friend class ReservationSys;
};

#endif

