#ifndef RESERVATION_SYS_H
#define RESERVATION_SYS_H

#include <iostream>
#include <vector>

using namespace std;

#include "Person.h"
#include "Group.h"

class ReservationSys
{
  private:
  static const int SMOKE_VALUE = 5;
  static const int COL_VALUE = 5;
  static const int ADJACENT_VALUE = 10;
  Person*** seats;
  vector<Group> groups;

  bool validSeating(vector<int> chosenSeatNums);
  int seatingValue(Group g, vector<int> chosenSeatNums);
  void incrementSeatNums(vector<int>& chosenSeatNums, int index);
  int aislesAvailable();

  public:
  static const int ROWS = 20;
  static const int COLS = 6;
  static const int SMOKE_ROWS = 3;
  ReservationSys();
  ~ReservationSys();
  bool addGroup(Group);
  bool removeGroup(Group*);
  bool save(string filename);
  bool load(string filename);
  void ticketGenerator(Group);
  void satisfactionReport();
  Person* getSeat(int row, int col){return seats[row][col];};
  vector<Group> getGroups(){return groups;};

  friend ostream& operator<<(ostream& out, ReservationSys& rhs);
};

#endif

