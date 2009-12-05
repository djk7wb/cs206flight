
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

  while (chosenSeatNums[0] <= ROWS*COLS - newGroup.members.size())
  {
    if (validSeating(chosenSeatNums))
    {
      newValue = seatingValue(newGroup, chosenSeatNums);
      if (newValue > bestValue)
      {
        bestValue = newValue;
        bestSeats = chosenSeatNums;
      }
    }
    chosenSeatNums.back() += 1;
    for (int i = chosenSeatNums.size()-1; i > 0; i--)
    {
      if (chosenSeatNums[i] > ROWS*COLS-chosenSeatNums.size()+i)
      {
        chosenSeatNums[i-1] += 1;
        for (int j = i; j < chosenSeatNums.size(); j++)
        {
          chosenSeatNums[j] = chosenSeatNums[j-1] + 1;
        }
      }
    }
  };

  if (bestValue != INVALID)
  {
    for (int i = 0; i < bestSeats.size(); i++)
    {
      int seatNum = bestSeats[i];
      seats[seatNum/COLS][seatNum%COLS] = new Person;
      *(seats[seatNum/COLS][seatNum%COLS]) = newGroup.members[i];
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
    for (int j = i+1; j < chosenSeatNums.size(); j++)
    {
      if (chosenSeatNums[i] == chosenSeatNums[j])
      {
        valid = false;
      }
    }
  }

  //Check occupied seats
  for (int i = 0; i < chosenSeatNums.size(); i++)
  {
    if (seats[chosenSeatNums[i]/COLS][chosenSeatNums[i]%COLS] != NULL)
    {
      valid = false;
    }
  }

  return valid;
}

int ReservationSys::seatingValue(Group g, vector<int> chosenSeatNums)
{
  const int SMOKE_VALUE = 10;
  const int COL_VALUE = 5;
  const int ADJACENT_VALUE = 15;
  int value = 0;

  sort(chosenSeatNums.begin(), chosenSeatNums.end());

  //Adjacency
  bool adjacent = true;
  int prevRow = -1;
  for (int i = 0; i < chosenSeatNums.size(); i++)
  {
    int seatNum = chosenSeatNums[i];
    int row = seatNum/COLS;
    int col = seatNum%COLS;
    bool aisle = (col==COLS/2 || col == COLS/2 -1);
    bool window = (col==0 || col == COLS-1);
    if (i > 0)
    {
      if (seatNum != chosenSeatNums[i-1]+1)
      {
        adjacent = false;
      }
      if (row != prevRow)
      {
        adjacent = false;
      }
    }
    prevRow = row;
    if ((g.type==BUSINESS)&&(g.smokingPreference == (row >= ROWS-SMOKE_ROWS)))
    {
      value += SMOKE_VALUE;
    }
    if (g.type==FAMILY && aisle)
    {
      value += COL_VALUE;
    }
    if (g.type==TOURISTS && window)
    {
      value += COL_VALUE;
    }
  }

  if (adjacent && chosenSeatNums.size()>1)
  {
    value += ADJACENT_VALUE;
  }

  return value;
}

ostream& operator<<(ostream& out, ReservationSys& rhs)
{
  for (int i = 0; i < rhs.ROWS; i++)
  {
    if (i == rhs.ROWS - rhs.SMOKE_ROWS)
    {
      out << "   Smoking\n";
    }
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

