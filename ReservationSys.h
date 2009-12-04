
#include <iostream>
#include <vector>

using namespace std;

class Person;
class Group;

class ReservationSys
{
  static const int ROWS = 30;
  static const int COLS = 6;
  Person** seats;
  bool addGroup(Group);
  bool removeGroup(Group);
  vector<Group> groups;
  bool save(string filename);
  bool load(string filename);
  void ticketGenerator(Group);
  void satisfactionReport();
};

