
#include "ReservationSys.h"

ReservationSys::ReservationSys()
{
  seats = new Person**[ROWS];
  for (int i = 0; i < ROWS; i++)
  {
    *(seats+i) = new Person*[COLS];
  }
  for (int i = 0; i < ROWS; i++)
  {
    for (int j = 0; j < COLS; j++)
    {
      seats[i][j] = NULL;
    }
  }
}

ReservationSys::~ReservationSys()
{
  for (int i = 0; i < ROWS; i++)
  {
    for (int j = 0; j < COLS; j++)
    {
      delete seats[i][j];
    }
  }
  for (int i = 0; i < ROWS; i++)
  {
    delete [] *(seats+i);
  }
  delete [] seats;
}

bool ReservationSys::addGroup(Group newGroup)
{
  const int INVALID = -9999;
  int bestValue = INVALID;
  vector<int> chosenSeatNums;
  vector<int> bestSeats;
  int newValue;

  for (int i = 0; i < newGroup.members.size(); i++)
  {
    chosenSeatNums.push_back(i);
  }

  while (chosenSeatNums[0] < ROWS*COLS - newGroup.members.size())
  {
    if (validSeating(chosenSeatNums))
    {
      newValue = seatingValue(newGroup, chosenSeatNums);
      if (newValue > bestValue)
      {
        cout << "better seat " <<  newValue;
        bestValue = newValue;
        bestSeats = chosenSeatNums;
      }
    }
    chosenSeatNums.back() += 1;
    for (int i = chosenSeatNums.size()-1; i >= 0; i--)
    {
      if (chosenSeatNums[i] > ROWS*COLS)
      {
        chosenSeatNums[i-1] += 1;
        chosenSeatNums[i] = chosenSeatNums[i-1] + 1;
      }
    }
  };

  if (bestValue != INVALID)
  {
    for (int i = 0; i < bestSeats.size(); i++)
    {
      int seatNum = bestSeats[i];
      seats[seatNum%ROWS][seatNum/ROWS] = new Person;
      *(seats[seatNum%ROWS][seatNum/ROWS]) = newGroup.members[i];
      cout << "chose " << seatNum << endl;
    }
    newGroup.satisfaction = bestValue;
  }
  return (bestValue != INVALID);
}

bool ReservationSys::validSeating(vector<int> chosenSeatNums)
{
  bool valid = true;
  //Check for duplicates
  for (int i = 0; i < chosenSeatNums.size()-1; i++)
  {
    //Check for duplicates
    for (int j = i; j < chosenSeatNums.size(); j++)
    {
      if (chosenSeatNums[i] == chosenSeatNums[j])
      {
        valid = false;
      }
    }
    if (seats[i] != NULL)
    {
      valid = false;
    }
  }

  return valid;
}

int ReservationSys::seatingValue(Group g, vector<int> chosenSeatNums)
{
  int value = 0;
  return value;
}

ostream& operator<<(ostream& out, ReservationSys& rhs)
{
  for (int i = 0; i < rhs.ROWS; i++)
  {
    for (int j = 0; j < rhs.COLS; j++)
    {
      if (j == rhs.COLS/2)
      {
        out << " ";
      }
      if (rhs.seats[i][j] == NULL)
      {
        out << "_ ";
      }
      else
      {
        out << "X ";
      }
    }
    out << "\n";
  }
  return out;
}

