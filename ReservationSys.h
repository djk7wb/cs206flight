#ifndef RESERVATION_SYS_H
#define RESERVATION_SYS_H

#include <iostream>
#include <vector>

#define _ROWS 20
#define _COLS 6
#define _SMOKE_ROWS 3

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
  Group groups[_ROWS*_COLS];
  int numGroups;

  bool validSeating(vector<int> chosenSeatNums);
  int seatingValue(Group g, vector<int> chosenSeatNums);
  void incrementSeatNums(vector<int>& chosenSeatNums, int index);
  int aislesAvailable();

  public:
  static const int ROWS = _ROWS;
  static const int COLS = _COLS;
  static const int SMOKE_ROWS = _SMOKE_ROWS;
  ReservationSys();
  ~ReservationSys();
  bool addGroup(Group);
  bool removeGroup(Group*);
  bool save(string filename);
  bool load(string filename);
  void ticketGenerator(Group);
  void satisfactionReport();
  Person* getSeat(int row, int col){return seats[row][col];};
  Group* getGroup(int row, int col);

  friend ostream& operator<<(ostream& out, ReservationSys& rhs);
};

#endif

