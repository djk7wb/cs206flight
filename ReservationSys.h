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
  static const int ROWS = 20;
  static const int COLS = 6;
  Person*** seats;
  vector<Group> groups;

  bool validSeating(vector<int> chosenSeatNums);
  int seatingValue(Group g, vector<int> chosenSeatNums);

  public:
  ReservationSys();
  ~ReservationSys();
  bool addGroup(Group);
  bool removeGroup(Group);
  bool save(string filename);
  bool load(string filename);
  void ticketGenerator(Group);
  void satisfactionReport();
};

#endif

